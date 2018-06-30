package engine;

import java.util.Objects;

public class Tags {
    private String nome;
    private long id;
    /**
    *@brief Construtor por omissao de Tags
    */
    public Tags(){
        this.nome="";
        this.id=0;
    }
    /**
    *@brief Construtor parametrizado e3   Tags
    */
    public Tags(String nome,long id) {
        this.nome = nome;
        this.id=id;
    }
    /**
    *@brief Construtor por copia de tags
    */
    public Tags(Tags t){
        this.nome=t.getNome();
        this.id=t.getId();
    }

    /**
    *Devolve o nome da Tag
    *
    * @return String
    */
    public String getNome() {
        return nome;
    }
    /**
         * Atualiza o nome da tag
         * @param String
         */
    public void setNome(String nome) {
        this.nome = nome;
    }
    /**
    *Devolve o id da tag
    *
    * @return long
    */
    public long getId() {
        return this.id;
    }
    /**
         * Atualiza o id da tag
         * @param long
         */
    public void setId(long ID) {
        this.id = id;
    }
    /**
         * Metodo clone
         * @return Tags
         */
    public Tags clone(){
        return new Tags(this);
    }

    /**
         * Metodo equals
         * @return boolean
         */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Tags tags = (Tags) o;
        return getId() == tags.getId() &&
                Objects.equals(getNome(), tags.getNome());
    }
    /**
         * Metodo toString
         * @return String
         */
    @Override
    public String toString() {
        return "Tags{" +
                "nome='" + nome + '\'' +
                ", id=" + id +
                '}';
    }
}
