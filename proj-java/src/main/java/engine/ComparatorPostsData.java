 package engine;
import java.util.Comparator;
/**
 * Write a description of class ComparatorUPosts here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class ComparatorPostsData implements Comparator<Posts>
{
  /**
  *@brief Função que compara dois posts por a data;
  *@param Posts
  *@param Posts
  *@return  int
  */
    public int compare(Posts c1, Posts c2) {
       return c1.getCreation_date().compareTo(c2.getCreation_date());
    }
}
