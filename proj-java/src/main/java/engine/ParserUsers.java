
/**
 * Write a description of class ParserUsers here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
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


  public class ParserUsers
  {
    /**
         * Faz o parser dos Users
         * @param String caminho dos ficheiros
         * @return Map<Long,Users>
         */
      public Map<Long,Users> Parser(String dump)  {
          Map<Long,Users> users=new TreeMap<>();
         try {

            SAXParserFactory spfactory = SAXParserFactory.newInstance();

            SAXParser saxParser = spfactory.newSAXParser();


            DefaultHandler handler = new DefaultHandler() {

            public void startElement(String uri, String localName,
                   String qName,Attributes attributes) throws SAXException{
                     if (qName.equals("row")) {
                      Long id = Long.parseLong(attributes.getValue("Id"));
                      int reputacao=Integer.parseInt(attributes.getValue("Reputation"));
                      String nome =attributes.getValue("DisplayName");
                      String bio =attributes.getValue("AboutMe");
                       Users u=new Users(id,reputacao,nome,bio,0);
                       users.put(id,u);

            }

          }


            public void endElement(String uri, String localName,
                     String qName) throws SAXException {

            }



            };

           saxParser.parse(dump+"Users.xml", handler);

         } catch (Exception e) {
           e.printStackTrace();
         }
         return users;
       }
    }
