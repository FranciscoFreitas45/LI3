   package engine;

import java.util.ArrayList;

public class Owner {
    private String name;
    private long ID;
    private int reputation;
    
    /**
    *@brief Construtor por omissao de Owner
    */
    public Owner(){
        this.name = " ";
        this.ID = 0;
        this.reputation = 0;
    }
    /**
    *@brief Construtor por copia de Owner
    */
    public Owner(Owner o){
        this.name = o.getName();
        this.ID = o.getID();
        this.reputation = o.getReputation();
    }
    /**
    *@brief Construtor parametrizado de Owner
    */
    public Owner(String nome, long id, int reputacao){
        this.name = nome;
        this.ID = id;
        this.reputation = reputacao;
    }

         /**
         *Devolve o nome do Owner
         *
         * @return o nome do Owner
         */
    public String getName() {
        return this.name;
    }
    /**
         * Atualiza o nome do owner
         * @param String nome
         */
    public void setName(String name) {
        this.name = name;
    }

        /**
         *Devolve o id do Owner
         *
         * @return o id do Owner
         */
    public long getID() {
        return this.ID;
    }

    /**
         * Atualiza o id do Owner
         *
         * @return long
         */
    public void setID(long ID) {
        this.ID = ID;
    }
        /**
         *Devolve a reputação do owner
         *
         * @return a reputacao do Owner
         */
    public int getReputation() {
        return this.reputation;
    }
    /**
         * Atualiza a reputacao do owner
         * @param int
         */
    public void setReputation(int reputation) {
        this.reputation = reputation;
    }
    /**
         *Metodo que clona um Owner
         *
         * @return Owner
         */
    public Owner clone(){
        return new Owner(this);
    }

    /**
         *Metodo que converte o Owner em String
         *
         * @return String
         */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\n").append("Name:" +this.name);
        sb.append("\n").append("ID:" +this.ID);
        sb.append("\n").append("Reputation:" +this.reputation);
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
        Owner owner = (Owner) o;
        return owner.getName().equals(this.name)
                && owner.getID() == this.ID
                && owner.getReputation() == this.reputation;
    }
}
