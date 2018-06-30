 package engine;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
/**
 * Write a description of class StringTotag here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class StringTotag
{
  /**
       * Converte uma string em um ArrayList, usado nas tags
       * @param string
       * @return List<String>
       */
       public List<String> parser(String tag) {
         List<String> result = new ArrayList<String>();


         if (tag!=null){
         StringTokenizer tokenizer =
                new StringTokenizer(tag, ";<>"); // your delimiter
        while (tokenizer.hasMoreElements()) {
             String token = tokenizer.nextToken();
            if (!(token.equals("gt")) && (!(token.equals("lt"))) && (!(token.equals("Tags=\""))) && (!(token.equals("\"")))){
                result.add(token);
            }

        }
    }
       return result;
}
    }
