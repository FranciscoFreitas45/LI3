package engine;

import java.util.Objects;

public class AuxTags {
    private String nome;
    private long id;
    private int num;
    /**
    *@brief Construtor por omissao de AuxTags
    */
    public AuxTags(){
        this.nome="";
        this.id=0;
        this.num=0;
    }
    /**
    *@brief Construtor parametrizado e3   AuxTags
    */
    public AuxTags(String nome,long id) {
        this.nome = nome;
        this.id=id;
        this.num = 1;
    }
    /**
    *@brief Construtor por copia de AuxTags
    */
    public AuxTags(AuxTags t){
        this.nome=t.getNome();
        this.id=t.getId();
        this.num = t.getNum();
    }

    /**
    *Devolve o nome da AuxTags
    *
    * @return String
    */
    public String getNome() {
        return nome;
    }
    /**
         * Atualiza o nome da AuxTags
         * @param String
         */
    public void setNome(String nome) {
        this.nome = nome;
    }
    /**
    *Devolve o id da AuxTags
    *
    * @return long
    */
    public long getId() {
        return this.id;
    }
    /**
         * Atualiza o id da AuxTags
         * @param long
         */
    public void setId(long ID) {
        this.id = id;
    }

    /**
    *Devolve o num da AuxTags
    *
    * @return int
    */
    public int getNum(){
      return this.num;
    }

    /**
         * Atualiza o id da AuxTags
         * @param int
         */
    public void setNum(int num){
      this.num = num;
    }
    /**
         * Metodo clone
         * @return AuxTags
         */
    public AuxTags clone(){
        return new AuxTags(this);
    }

    /**
         * Metodo equals
         * @return boolean
         */

         /**
              * Metodo is the same tag
              * @return boolean
              */

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AuxTags auxtags = (AuxTags) o;
        return getId() == auxtags.getId();
    }
    /**
         * Metodo toString
         * @return String
         */
    @Override
    public String toString() {
      StringBuilder sb = new StringBuilder();
      sb.append("\n").append("Tag: " + this.nome);
      sb.append("\n").append("ID: " +this.id);
      sb.append("\n").append("                  Num: " +this.num);
      return sb.toString();
    }
}
