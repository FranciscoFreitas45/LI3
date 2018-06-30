 package engine;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Posts {
    private long ID;
    private String title;
    private long ownerID;
    private Owner autor;
    private short typeID;
    private long parentID;
    private LocalDate creation_date;
    private List<String> tag;
    private int score;
    private int comentCount;
    private int answerCount;

    /**
    *@brief Construtor por omissao de Posts
    */
    public Posts(){
        this.ID = 0;
        this.title = "";
        this.ownerID = 0;
        this.autor = new Owner();
        this.typeID = 0;
        this.parentID = 0;
        this.creation_date = LocalDate.now();
        this.tag = new ArrayList<>();
        this.score = 0;
        this.comentCount = 0;
        this.answerCount = 0;
    }
    /**
    *@brief Construtor por copia de Posts
    */
    public Posts(Posts p){
        this.ID = p.getID();
        this.title = p.getTitle();
        this.ownerID = p.getOwnerID();
        this.autor = p.getAutor();
        this.typeID = p.getTypeID();
        this.parentID = p.getParentID();
        this.creation_date = p.getCreation_date();
        this.tag = p.getTag();
        this.score = p.getScore();
        this.comentCount = p.getComentCount();
        this.answerCount = p.getAnswerCount();
    }
    /**
    *@brief Construtor parametrizado de Posts
    */
    public Posts(long id, String titulo, long ownerid, Owner author, short typeid, long parentid, LocalDate creationdate, List<String> tags, int score, int comentCount, int answerCount){
        this.ID = id;
        this.title = titulo;
        this.ownerID = ownerid;
        this.autor = author;
        this.typeID = typeid;
        this.parentID = parentid;
        this.creation_date = creationdate;
        this.tag = tags;
        this.score = score;
        this.comentCount = comentCount;
        this.answerCount = answerCount;
    }
    /**
    *Devolve o id do Post
    *
    * @return  o id do Post
    */
    public long getID() {
        return this.ID;
    }
    /**
         * Atualiza o id do Post
         * @param long
         */
    public void setID(long ID) {
        this.ID = ID;
    }
    /**
    *Devolve o titulo do Post
    *
    * @return  o titulo do Post
    */
    public String getTitle() {
        return this.title;
    }
    /**
         * Atualiza o titulo do Post
         * @param String
         */
    public void setTitle(String title) {
        this.title = title;
    }
    /**
    *Devolve o id do owner do post
    *
    * @return  o id do owner do post
    */
    public long getOwnerID() {
        return this.ownerID;
    }
    /**
         * Atualiza o id do owner do Post
         * @param long
         */
    public void setOwnerID(long ownerID) {
        this.ownerID = ownerID;
    }
    /**
    *Devolve o owner do post
    *
    * @return   o owner do post
    */
    public Owner getAutor() {
        return this.autor;
    }
    /**
         * Atualiza o owner do post
         * @param Owner
         */
    public void setAutor(Owner autor) {
        this.autor = autor.clone();
    }
    /**
    *Devolve o tipo do post
    *
    * @return  o tipo  do post
    */
    public short getTypeID() {
        return this.typeID;
    }
    /**
         * Atualiza o tipo  do Post
         * @param short
         */
    public void setTypeID(short typeID) {
        this.typeID = typeID;
    }
    /**
    *Devolve o Parentid do post
    *
    * @return  o Parentid do post
    */
    public long getParentID() {
        return this.parentID;
    }
    /**
         * Atualiza o parentid do Post
         * @param long
         */
    public void setParentID(long parentID) {
        this.parentID = parentID;
    }
    /**
    *Devolve a data do post
    *
    * @return LocalDate
    */
    public LocalDate getCreation_date() {
        return this.creation_date;
    }
    /**
         * Atualiza a data  do Post
         * @param LocalDate
         */
    public void setCreation_date(LocalDate creation_date) {
        this.creation_date = creation_date;
    }
    /**
    *Devolve as tags do post
    *
    * @return List<String>
    */
    public List<String> getTag() {
      List<String> aux= new ArrayList<>();
      for(String s :this.tag){
          aux.add(s);
      }
        return aux;
    }
    /**
         * Atualiza as tags do Post
         * @param ArrayList<String>
         */
    public void setTag(ArrayList<String> tag) {
       this.tag= new ArrayList<>();
      for(String s :tag){
          this.tag.add(s);
      }
    }
    /**
    *Devolve o score do post
    *
    * @return int
    */
    public int getScore() {
        return this.score;
    }
    /**
         * Atualiza o Score do Post
         * @param int
         */
    public void setScore(int score) {
        this.score = score;
    }
    /**
    *Devolve o numero de comentarios do post
    *
    * @return int
    */
    public int getComentCount() {
        return this.comentCount;
    }
    /**
         * Atualiza o CommentCount do Post
         * @param int
         */
    public void setComentCount(int comentCount) {
        this.comentCount = comentCount;
    }
    /**
    *Devolve o numero de respostas do post
    *
    * @return int
    */
    public int getAnswerCount() {
        return this.answerCount;
    }
    /**
         * Atualiza o answerCount do Post
         * @param int
         */
    public void setAnswerCount(int answerCount) {
        this.answerCount = answerCount;
    }

    /**
    *Metodo clone
    *
    * @return Posts
    */
    public Posts clone(){
        return new Posts(this);
    }
    /**
    *Metodo equals
    *
    * @return bolean
    */
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (obj == null || obj.getClass() != this.getClass()) return false;
        Posts p = (Posts) obj;
        return p.getID() == this.ID
                && p.getTitle().equals(this.title)
                && p.getOwnerID() == this.ownerID
                && p.getAutor().equals(this.autor)
                && p.getTypeID() ==this.typeID
                && p.getParentID() == this.parentID
                && p.getCreation_date().equals(this.creation_date)
                && p.getTag().equals(this.tag)
                && p.getScore() == this.score
                && p.getComentCount() == this.comentCount
                && p.getAnswerCount() == this.answerCount;
    }
    /**
    *Metodo toString
    *
    * @return String
    */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n").append("ID:" + this.ID);
        sb.append("\n").append("Title:" +this.title);
        sb.append("\n").append("OwnerID:" +this.ownerID);
        sb.append("\n").append("Autor:" +this.autor);
        sb.append("\n").append("TypeID" +this.typeID);
        sb.append("\n").append("ParentID:" +this.parentID);
        sb.append("\n").append("Creation Date:" +this.creation_date);
        sb.append("\n").append("Tag:" +this.tag);
        sb.append("\n").append("Score:" +this.score);
        sb.append("\n").append("Comment Count:" +this.comentCount);
        sb.append("\n").append("Answer:" +this.answerCount);
        return sb.toString();
    }
}
