  package engine;
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
 * Write a description of class TCD here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class TCD
{
   private Map<Long,Posts> posts;
   private Map<Long,Users> users;
   private Map<Long,List<Posts>> postsUser;
   private Map<LocalDate,List<Posts>> dataposts;
   private Map<String,Tags> tags;
   /**
   *@brief Construtor por omissao de TCD
   */
   public  TCD(){
       this.posts=new TreeMap<>();
       this.users=new TreeMap<>();
       this.postsUser=new TreeMap<>();
       this.dataposts =new TreeMap<>();
       this.tags = new HashMap<>();
    }

    /**
    *@brief Construtor por parametros  de TCD
    */
    public TCD(Map<Long,Posts> posts,Map<Long,Users> users,Map<String,Tags> tags){
        setPosts(posts);
        setUsers(users);
        setTags(tags);
        setPostsUsers();
        setDataPosts();

    }
    /**
    *@brief Construtor por copia de TCD
    */
    public TCD (TCD t){
        this.posts=t.getPosts();
        this.users=t.getUsers();
        this.tags=t.getTags();
        this.postsUser=t.getPostsUsers();
        this.dataposts=t.getPostsData();
    }
    //gets
    /**
    *@brief Devolve o Map dos Posts
    *@return Map<Long,Posts>
    */
   public Map<Long,Posts> getPosts(){
       Map<Long,Posts> aux= new TreeMap<>();
       for(Posts p: this.posts.values())
            aux.put(p.getID(),p.clone());
            return aux;
    }
    /**
    *@brief Devolve o Map dos Users
    *@return Map<Long,Users>
    */
    public Map<Long,Users> getUsers(){
       Map<Long,Users> aux= new TreeMap<>();
       for(Users u: this.users.values())
            aux.put(u.getID(),u.clone());
            return aux;
    }
    /**
    *@brief Devolve o Map dos posts em que a key é o id do user;
    *@return Map<Long,List<Posts>>
    */
    public Map<Long,List<Posts>> getPostsUsers(){
                Map<Long,List<Posts>> aux =new HashMap<>();

            List<Posts> auxx;
            for(List<Posts> pp : this.postsUser.values())  {
                for(Posts p :pp)
                    if (aux.containsKey(p.getOwnerID())){
                       auxx=  aux.get(p.getOwnerID());
                       auxx.add(p);

                 }
                 else{
                    List<Posts> aux2=new ArrayList<>();
                    aux2.add(p);
                    aux.put(p.getOwnerID(),aux2);
                 }

        }
              return aux;
            }

            /**
            *@brief Devolve o Map dos posts em que a key é a data;
            *@return Map<LocalDate,List<Posts>>
            */
        public Map<LocalDate,List<Posts>> getPostsData(){
                Map<LocalDate,List<Posts>> aux =new HashMap<>();

            List<Posts> auxx;
            for(List<Posts> pp : this.dataposts.values())  {
                for(Posts p :pp)
                    if (aux.containsKey(p.getCreation_date())){
                       auxx=  aux.get(p.getCreation_date());
                       auxx.add(p);

                 }
                 else{
                    List<Posts> aux2=new ArrayList<>();
                    aux2.add(p);
                    aux.put(p.getCreation_date(),aux2);
                 }

               }
              return aux;
            }

    /**
    *@brief Devolve o Map das Tags
    *@return Map<String,Tags>
    */
    public Map<String,Tags> getTags(){
        Map<String,Tags> aux= new HashMap<>();
        for(Tags t: this.tags.values())
            aux.put(t.getNome(),t.clone());
        return aux;
    }

    //sets
    /**
         * @brief Atualiza o map de Posts
         * @param Map<Long,Posts>
         */

    public void setPosts(Map<Long,Posts> aux){
         this.posts= new TreeMap<>();
       for(Posts p:aux.values())
            this.posts.put(p.getID(),p.clone());
        }
        /**
             * @brief Atualiza o map de Users
             * @param Map<Long,Users>
             */

    public void setUsers(Map<Long,Users> aux){
         this.users= new TreeMap<>();
       for(Users u:aux.values())
            this.users.put(u.getID(),u.clone());
        }
        /**
             * @brief Atualiza  map de Posts
             */
        public void setPostsUsers(){
            this.postsUser =new HashMap<>();

            List<Posts> auxx;

                for(Posts p :this.posts.values())
                    if (this.postsUser.containsKey(p.getOwnerID())){
                       auxx=  this.postsUser.get(p.getOwnerID());
                       auxx.add(p);

                 }
                 else{
                    List<Posts> aux2=new ArrayList<>();
                    aux2.add(p);
                    this.postsUser.put(p.getOwnerID(),aux2);
                 }


    }
    /**
         * @brief Atualiza o map de Posts por data
         */
     public void setDataPosts(){
            this.dataposts =new TreeMap<>(new ComparatorDatas() );

            List<Posts> auxx;

                for(Posts p :this.posts.values())
                    if (this.dataposts.containsKey(p.getCreation_date())){
                       auxx=  this.dataposts.get(p.getCreation_date());
                       auxx.add(p);

                 }
                 else{
                    List<Posts> aux2=new ArrayList<>();
                    aux2.add(p);
                    this.dataposts.put(p.getCreation_date(),aux2);
                 }


    }
    /**
         * @brief Atualiza  map de tags
         * @param Map<String,Tags>
         */
    public void setTags(Map<String,Tags> aux){
        this.tags= new HashMap<>();
        for(Tags t:aux.values())
            this.tags.put(t.getNome(),t.clone());
    }

    /**
         * @brief completa  os campos null no objetos
         */
     public void completa(){
         long id;
         Users u;
         int reputacao;
         String nome;


         for(Posts p : this.posts.values()){
             id =p.getOwnerID();
            if(this.users.containsKey(id)){
                u =this.users.get(id);

                nome=u.getName();
                reputacao=u.getReputation();
                Owner o= new Owner(nome,id,reputacao);
                p.setAutor(o);
                int x= u.getNumPosts();
                u.setNumPosts(x+1);



        }
    }
}


/**
     *@brief Metodo clone
     * @return TCD
     */
     public TCD clone(){
         return new TCD(this);
        }

        /**
             *@brief Metodo equals
             * @return boolean
             */
        public boolean equals(Object o) {
      if (this == o)
        return true;
      if ((o == null) || (this.getClass() != o.getClass()))
        return false;
      TCD t = (TCD) o;
      return this.posts.equals(t.getPosts()) && this.users.equals(t.getUsers()) && this.postsUser.equals(t.getPostsUsers())
      && this.dataposts.equals(t.getPostsData()) && this.tags.equals(t.getTags());

   }

   public void clear(){
    this.posts.clear();
    this.users.clear();
    this.postsUser.clear();
    this.dataposts.clear();
    this.tags.clear();
    this.posts = new TreeMap<>();
    this.users = new TreeMap<>();
    this.postsUser = new TreeMap<>();
    this.dataposts = new TreeMap<>();
    this.tags = new HashMap<>();

   }


}
