package engine;
import java.util.Comparator;
/**
* Write a description of class ComparatorUPosts here.
*
* @author (your name)
* @version (a version number or a date)
*/
public class ComparatorAuxtags implements Comparator<AuxTags>
{
 /**
 *@brief Função que compara dois posts por a data;
 *@param AuxTags
 *@param AuxTags
 *@return  int
 */
 public int compare(AuxTags c1, AuxTags c2) {
    if(c1.getNum() < c2.getNum()){
        return 1;
     }else if(c1.getNum() > c2.getNum()){
         return -1;
     }
     return 0;
 }
}
