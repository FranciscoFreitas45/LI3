 package engine;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.Iterator;
import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;


public class Users {
    private long ID;
    private int reputation;
    private String name;
    private String bio;
    private int numPosts;


    /**
    *@brief Construtor por omissao de Users
    */
    public Users(){
        this.ID=0;
        this.reputation=0;
        this.name="";
        this.bio="";
        this.numPosts=0;

    }

    /**
    *@brief Construtor parametrizado de Users
    */
    public Users(long ID,int reputation,String name,String bio,int numPosts){
        this.ID=ID;
        this.reputation=reputation;
        this.name=name;
        this.bio=bio;
        this.numPosts=numPosts;
    }

    /**
    *@brief Construtor por copia de Users
    */
    public Users(Users u){
        this.ID=u.getID();
        this.reputation=u.getReputation();
        this.name=u.getName();
        this.bio=u.getBio();
        this.numPosts=u.getNumPosts();

    }

    /**
    *Devolve o id do User
    *
    * @return o id do User
    */
    public long getID() {
        return this.ID;
    }
    /**
    * Atualiza o id do user
    * @param long id do User
    */
    public void setID(long ID) {
        this.ID = ID;
    }
    /**
    *Devolve a reputação do User
    *
    * @return da repução
    */
    public int getReputation() {
        return this.reputation;
    }
    /**
    * Atualiza a reputação do User
    * @param int reputação
    */
    public void setReputation(int reputation) {
        this.reputation = reputation;
    }
    /**
    *Devolve o nome do User
    *
    * @return o nome do User
    */
    public String getName() {
        return this.name;
    }

    /**
    * Atualiza o nome do User
    * @param String nome do User
    */
    public void setName(String name) {
        this.name = name;
    }

    /**
    *Devolve a Bio do User
    *
    * @return a Bio do User
    */
    public String getBio() {
        return this.bio;
    }
    /**
    * Atualiza a short Bio do User
    * @param int short Bio do User
    */
    public void setBio(String bio) {
        this.bio = bio;
    }

    /**
    *Devolve o números de Posts do User
    *
    * @return o número de Posts do User
    */
    public int getNumPosts() {
        return this.numPosts;
    }
    /**
    * Atualiza o nome do owner
    * @param int números Posts
    */
    public void setNumPosts(int numPosts) {
        this.numPosts = numPosts;
    }




    /**
    *Metodo que clona um User
    *
    * @return User
    */
    public Users clone(){
        return new Users(this);
    }
    /**
    *Metodo que converte o User em String
    *
    * @return String
    */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n").append("ID:" +this.ID);
        sb.append("\n").append("\n").append("REPUTAÇAOO:" +this.reputation);
        sb.append("\n").append("NOME:" +this.name);
        sb.append("\n").append("BIO:" +this.bio);
        sb.append("\n").append("NUMERO DE POSTS:" +this.numPosts);

        return sb.toString();
    }
    /**
    *Metodo equals
    *
    * @return boolean
    */
    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;
        Users u = (Users) o;
        return u.getID()==(this.ID)
                && u.getReputation() == this.reputation
                && u.getName().equals(this.name)
                && u.getBio().equals(this.bio)
                && u.getNumPosts() == this.numPosts;
    }
}
