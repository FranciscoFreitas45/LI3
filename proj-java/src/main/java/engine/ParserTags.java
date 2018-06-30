
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
import java.time.LocalDateTime;
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
public class ParserTags
{
  /**
       * Faz o parser das tags
       * @param String caminho dos ficheiros
       * @return Map<Long,Tags>
       */
    public Map<String,Tags> Parser(String dump)  {
        Map<String,Tags> tags=new HashMap<>();
        try {

            SAXParserFactory spfactory = SAXParserFactory.newInstance();

            SAXParser saxParser = spfactory.newSAXParser();


            DefaultHandler handler = new DefaultHandler() {

                public void startElement(String uri, String localName,
                                         String qName,Attributes attributes) throws SAXException{
                    if (qName.equals("row")) {
                        long id = Long.parseLong(attributes.getValue("Id"));
                        String nome =attributes.getValue("TagName");
                        Tags t=new Tags(nome,id);
                        tags.put(nome,t);

                    }

                }


                public void endElement(String uri, String localName,
                                       String qName) throws SAXException {

                }



            };

            saxParser.parse(dump+"Tags.xml", handler);

        } catch (Exception e) {
            e.printStackTrace();
        }
        return tags;
    }
}
