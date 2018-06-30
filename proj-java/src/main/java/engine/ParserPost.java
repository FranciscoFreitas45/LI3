 package engine;
import java.io.IOException;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import java.io.File;
import java.util.Locale;
import java.time.format.DateTimeFormatter;
import java.time.LocalDate;
import java.util.TreeSet;
import java.util.Set;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;

/**
 * Write a description of class ParserPost here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class ParserPost
{
  /**
       * Faz o parser dos posts
       * @param String caminho dos ficheiros
       * @return Map<Long,Posts>
       */
    public Map<Long,Posts> Parser(String dump)  {
                Map<Long,Posts> posts =new TreeMap<>();
         try {
            SAXParserFactory spfactory = SAXParserFactory.newInstance();

            SAXParser saxParser = spfactory.newSAXParser();



            DefaultHandler handler = new DefaultHandler() {

            public void startElement(String uri, String localName,
                   String qName,Attributes attributes) throws SAXException{
                   if (qName.equals("row")) {
                    Long id = Long.parseLong(attributes.getValue("Id"));
                    String titulo=attributes.getValue("Title");
                    int ownerId =Integer.parseInt(attributes.getValue("OwnerUserId"));
                    short typeId =Short.parseShort(attributes.getValue("PostTypeId"));
                    long parentId=0;
                    if(typeId==2)
                     parentId =Long.parseLong(attributes.getValue("ParentId"));
                     String date =attributes.getValue("CreationDate");
                     DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd'T'HH:mm:ss.SSS", Locale.ENGLISH);
                     LocalDate creation_date = LocalDate.parse(date, formatter);
                     String tags=attributes.getValue("Tags");
                     List<String> taggs= new ArrayList<>();
                     StringTotag s=new StringTotag();
                     taggs=s.parser(tags);
                     int score = Integer.parseInt(attributes.getValue("Score"));
                     int commentCount = Integer.parseInt(attributes.getValue("CommentCount"));
                     int answerCount =0;
                    if(typeId==1)
                     answerCount = Integer.parseInt(attributes.getValue("AnswerCount"));
                     Posts p=new Posts(id,titulo,ownerId, null,typeId,parentId,creation_date,taggs,score,commentCount,answerCount);
                     posts.put(id,p.clone());

            }

        }


            public void endElement(String uri, String localName,
                     String qName) throws SAXException {

            }



            };

           saxParser.parse(dump+"Posts.xml", handler);

         } catch (Exception e) {
           e.printStackTrace();
         }
         return posts;
       }


}
