package engine;
import java.util.Comparator;
/**
 * Write a description of class ComparatorUPosts here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class ComparatorUPosts implements Comparator<Users>
{
  /**
  *@brief Função que compara dois users por o numero de posts
  *@param Users
  *@param Users
  *@return  int
  */
    public int compare(Users c1, Users c2) {
       if(c1.getNumPosts() < c2.getNumPosts()){
           return 1;
        }else if(c1.getNumPosts() > c2.getNumPosts()){
            return -1;
        }
        return 0;
    }

}
