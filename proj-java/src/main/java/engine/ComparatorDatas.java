  package engine;
import java.util.Comparator;
import java.time.LocalDate;
/**
 * Write a description of class ComparatorDatas here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */

 /**
 *@brief Classe que tem um compator de Datas utilizada pelo g_tree_foreach para acabar de preencher as GTrees.
 */
public class ComparatorDatas implements Comparator<LocalDate>

{

  /**
  *@brief Função que compara duas datas
  *@param LocalDate
  *@param LocalDate da Gtree de posts
  *@return  int
  */
    public int compare(LocalDate c1, LocalDate c2) {
       return c1.compareTo(c2);
    }
}
