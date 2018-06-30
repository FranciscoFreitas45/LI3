  package engine;
import common.MyLog;
import common.Pair;
import li3.TADCommunity;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.time.LocalDate;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.Stream;
import java.util.stream.Collectors;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Set;
import java.util.TreeSet;
import java.util.Iterator;


public class MYTCDExample implements TADCommunity {
    private TCD tcd;
    private MyLog qelog;

    /*
    public void init() {
        this.qelog = new MyLog("queryengine");
    }
    */
    /**
    *@brief Função que carrega o objeto TCD
    *@param String caminho para os ficheiros
    */
    public void load(String dumpPath) {
        ParserPost p = new ParserPost();
        ParserUsers u =new ParserUsers();
        ParserTags t= new ParserTags();

        Map<Long,Posts> posts=p.Parser(dumpPath);
        Map<Long,Users> users=u.Parser( dumpPath);
        Map<String,Tags> tags= t.Parser(dumpPath);


          this.tcd= new TCD(posts,users,tags);
        this.tcd.completa();
    }
    /**
    * @brief Dado um id de um post, ve a informacao relativa ao post(titulo do post)
    * e nome de utilizador do autor
    * @param id do post
    * @return Pair<String,String>
    */
    // Query 1
    public Pair<String,String> infoFromPost(long id) {
        Map<Long,Posts> posts = this.tcd.getPosts();
        Posts post = posts.get(id);
        String titulo;
        String utilizador;

        if(post!=null){
            if(post.getTypeID() == 1){
            titulo = post.getTitle();
            utilizador = post.getAutor().getName();
            return new Pair(titulo,utilizador);
        }
           else if(post.getTypeID() == 2){
               post = posts.get(post.getParentID());
               if(post!=null){
                   titulo = post.getTitle();
                   utilizador = post.getAutor().getName();
                   return new Pair(titulo,utilizador);
               }
               else{
                 System.out.println("Resposta sem a pergunta correspondente no ficheiro");
                }
        }
        else{
            System.out.println("Id de um post que não é pergunta nem resposta");
        }

        }
        else{
        System.out.println("Id de post que não está no ficheiro");
        }
        titulo= "";
        utilizador="";
        return new Pair(titulo,utilizador);

    }

    /**
    * @brief Obtem os N utilizadores com mais atividade de sempre, ou seja, com maior
    * numero de posts de sempre, sendo consideradas tanto perguntas como respostas
    * @param N
    * @return List<Long>
    */
    // Query 2
    public List<Long> topMostActive(int N) {

        Map<Long,Users> users = this.tcd.getUsers();
        List<Users> novo = users.values().stream().collect(Collectors.toList());
        novo.sort(new ComparatorUPosts());
        List<Long> fim = novo.stream().map(Users::getID).collect(Collectors.toList()).subList(0,N);
        return fim;



    }
    /**
    * @brief De acordo com o intervalo de tempo dado, calcula numero total de posts
    * dentro da data, identificando perguntas e respostas
    * @param begin
    * @param end
    * @return Pair<Long,Long>
    */
    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {

        long perguntas= 0;
        long respostas= 0;
        List<Posts> posts = this.tcd.getPostsData().values().stream()
                     .flatMap(List::stream)
                     .filter(a-> a.getCreation_date().isAfter(begin) && a.getCreation_date().isBefore(end))
                     .collect(Collectors.toList());
                for(Posts p: posts){
                    if(p.getTypeID() == 1)
                    perguntas++;
                    else if(p.getTypeID() == 2)
                    respostas++;

                }
                return new Pair(perguntas,respostas);

    }

    /**
    * @brief De acordo com a data dada,calcula todas as perguntas que contem uma certa tag
    * ordenando por ordem cronologica inversa
    * @param tag
    * @param begin
    * @param end
    * @return List<Long>
    */
    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {

        List<Posts> posts = this.tcd.getPostsData().values().stream()
                     .flatMap(List::stream).filter(a-> a.getCreation_date().isAfter(begin) && a.getCreation_date().isBefore(end) || a.getCreation_date().isEqual(begin) || a.getCreation_date().isEqual(end))
                     .filter(a -> a.getTag().contains(tag))
                     .collect(Collectors.toList());
        Collections.sort(posts, new ComparatorPostsDataInv());

        List<Long> fim = posts.stream().map(Posts::getID).collect(Collectors.toList());

        return fim;

    }
    /**
    * @brief Com o ID de um autor, retira a informacao da short bio dele, e os IDS
    * dos ultimos 10 posts efetuados por ele
    * @param id
    * @return Pair<String,Lis<Long>>
    */
    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {

        Users user = this.tcd.getUsers().get(id);
        String bio;
        List<Long> vazio = new ArrayList<>();
        if(user!=null){
            bio = user.getBio();
        }
        else{
            System.out.println("User inexistente");
            return new Pair("",vazio);
        }
        List<Posts> posts = this.tcd.getPostsUsers().get(id);
        if(posts!=null){
            posts.sort(new ComparatorPostsDataInv());
            List<Long> ids= posts.stream().map(Posts::getID).collect(Collectors.toList()).subList(0,10);


            return new Pair(bio,ids);
        }else{
            List<Long> ids = new ArrayList<>();
            System.out.println("User nao tem posts\n");
            return new Pair(bio,ids);
        }


    }
    /**
    * @brief Dentro de um certo intervalo de tempo devolver as N perguntas com mais
    * votos, em ordem decrescente do numero de votos
    * @param N
    * @param begin
    * @param end
    * @return List<Long>
    */
    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
          List<Posts> posts = this.tcd.getPostsData().values().stream()
                     .flatMap(List::stream)
                     .filter(a-> a.getCreation_date().isAfter(begin) && a.getCreation_date().isBefore(end) || a.getCreation_date().isEqual(begin) || a.getCreation_date().isEqual(end))
                     .filter(a -> a.getTypeID() == 2)
                     .collect(Collectors.toList());
        posts.sort(new ComparatorPostsScore());
        List<Long> fim = posts.stream().map(Posts::getID).collect(Collectors.toList()).subList(0,N);

        return fim;



    }
    /**
    * @brief Calcula os IDS das N perguntas com mais respostas, dentro de um certo
    * intervalo de tempo
    * @param N
    * @param begin
    * @param end
    * @return List<Long>
    */
    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        List<Posts> posts = this.tcd.getPostsData().values().stream()
                     .flatMap(List::stream)
                     .filter(a-> a.getCreation_date().isAfter(begin) && a.getCreation_date().isBefore(end) || a.getCreation_date().isEqual(begin) || a.getCreation_date().isEqual(end))
                     .filter(a -> a.getTypeID() == 1)
                     .collect(Collectors.toList());
        posts.sort(new ComparatorNumRespostas());
        List<Long> fim = posts.stream().map(Posts::getID).collect(Collectors.toList()).subList(0,N);
        return fim;

    }
    /**
    * @brief Dado uma palavra, dar os IDS das N perguntas que contenham a palavra
    * dada (word)
    * @param word
    * @param N
    * @return List<Long>
    */
    // Query 8
    public List<Long> containsWord(int N, String word) {
      String cur;
      List<Posts> posts = new ArrayList<>();
      for(Posts p : this.tcd.getPosts().values() ){
          cur = p.getTitle();
          try{
            if(cur.contains(word))
            posts.add(p);
          }
          catch(NullPointerException e){}
      }
      posts.sort(new ComparatorPostsDataInv());
      List<Long> fim = posts.stream().map(Posts::getID).collect(Collectors.toList()).subList(0,N);
      return fim;

    }
    /**
    * @brief Dado os IDS de dois utilizadores, devolver as ultimas N perguntas em
    * que ambos participaram, via pergunta ou resposta, por ordem cronologica inversa
    * @param id1
    * @param id2
    * @param N
    * @return List<Long>
    */
    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) {
        List<Posts> posts1 = new ArrayList<>();
        List<Posts> posts2 = new ArrayList<>();
        List<Posts> u1 = this.tcd.getPostsUsers().get(id1);
        List<Posts> u2 = this.tcd.getPostsUsers().get(id2);
        Posts aux;
        if(u1 != null && u2 !=null){
          for(Posts p : u1){
            if(p.getTypeID()==1){
              posts1.add(p.clone());
            }
            else if(p.getTypeID()==2){
              aux = this.tcd.getPosts().get(p.getParentID());
              if(aux != null){
                posts1.add(aux.clone());
              }
            }
          }
          for(Posts p : u2){
            if(p.getTypeID()==1){
              posts2.add(p.clone());
            }
            else if(p.getTypeID()==2){
              aux = this.tcd.getPosts().get(p.getParentID());
              if(aux != null){
                posts2.add(aux.clone());
              }
            }
          }
        }
        List<Posts> auxfim = new ArrayList<>();
        for(Posts p : posts1){
          if(posts2.contains(p)){
            if(!auxfim.contains(p))
            auxfim.add(p.clone());
          }
        }
        auxfim.sort(new ComparatorPostsDataInv());
        List<Long> fim = new ArrayList<>();
        try{
          fim = auxfim.stream().map(Posts::getID).collect(Collectors.toList()).subList(0,N);
        }catch(IndexOutOfBoundsException e){
          fim = auxfim.stream().map(Posts::getID).collect(Collectors.toList());
        }
      return fim;
    }
    /**
    * @brief Dado o ID de uma pergunta, obter a melhor resposta.
    * @param id1
    * @param id2
    * @param N
    * @return long
    */
    // Query 10
    public long betterAnswer(long id) {
      Map<Long,Posts> p = this.tcd.getPosts();
      Posts pp = p.get(id);
      long l,res;
      res = 0;
      double d = 0;
      double max = 0;
        if ( pp != null ) {
          long answerCount = pp.getAnswerCount();
          Iterator<Posts> it = p.values().iterator();
          Posts ppp;
          int i = 0;
          while ( it.hasNext() && i < answerCount ){
            ppp = it.next();
            l = ppp.getParentID();
              if ( l == id ){
                d = (ppp.getScore() * 0.65) + (ppp.getAutor().getReputation() * 0.25)
                  + (ppp.getComentCount() * 0.1);
                i++;
                if ( d > max ) {
                  max = d;
                  res = ppp.getID();
                }
              }
          }
        }
        else {
          return -1;
        }
        return res;
    }


    /**
    * @brief Dentro de um dado intervalo de tempo, devolve as N tags mais usadas
    * pelos N utilizadores com melhor reputacao, por ordem decrescente do numero
    * de vezes em que a tag e utilizada
    * @param N
    * @param begin
    * @param end
    * @return Retorna um LONG_list
    */
    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
      List<Posts> posts = this.tcd.getPostsData().values().stream()
                   .flatMap(List::stream)
                   .filter(a-> a.getCreation_date().isAfter(begin) && a.getCreation_date().isBefore(end) || a.getCreation_date().isEqual(begin) || a.getCreation_date().isEqual(end))
                   .collect(Collectors.toList());
                   posts.sort(new ComparatorPostsBestRep());
                   List<Long> ids = posts.stream().map(Posts::getOwnerID).distinct().collect(Collectors.toList());
                    try{
                      ids = ids.subList(0,N);
                    }
                    catch(IndexOutOfBoundsException e){
                    }
      List<AuxTags> auxtags = new ArrayList<>();
      String str ="";
      Tags tag;
      AuxTags auxtag;
      for(Posts p : posts){
        if(ids.contains(p.getOwnerID())){
        for(String s : p.getTag()){
          tag = this.tcd.getTags().get(s);
          if(tag != null){
            auxtag= new AuxTags(tag.getNome(),tag.getId());
            if(auxtags.contains(auxtag)){
              auxtag = auxtags.get(auxtags.indexOf(auxtag));
              auxtag.setNum(auxtag.getNum()+1);
            }
            else {
              auxtags.add(auxtag);
            }
          }
        }
      }
      }
      auxtags.sort(new ComparatorAuxtags());
      List<Long> fim = auxtags.stream().map(AuxTags::getId).collect(Collectors.toList());
      try{
        fim = fim.subList(0,N);
      }
      catch(IndexOutOfBoundsException e){
      }
      return fim;
    }

    public void clear(){
     this.tcd.clear();
    }
  }
