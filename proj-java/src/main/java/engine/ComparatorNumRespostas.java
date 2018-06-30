package engine;
import java.util.Comparator;
/**
 * Write a description of class ComparatorUPosts here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class ComparatorNumRespostas implements Comparator<Posts>
{
  /**
  *@brief Função que compara dois posts por o answerCount
  *@param Posts
  *@param Posts 
  *@return  int
  */
    public int compare(Posts c1, Posts c2) {
       if(c1.getAnswerCount() < c2.getAnswerCount()){
           return 1;
        }else if(c1.getAnswerCount() > c2.getAnswerCount()){
            return -1;
        }
        return 0;
    }
}
