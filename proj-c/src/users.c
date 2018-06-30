#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"
#include "common.h"
#include "posts.h"
#include "data.h"


/**
* @file users.c
* @author Grupo56
* @date 5 May 2018
* @brief Informações relativas ao user
*/
struct users{
    long id;
    int reputation;
    char* name;
    char* bio;
    int numposts;
    Post *lista_posts;
};





/**
* @brief Cria a informação relativa ao user
* @param id Id do user
* @param reputation Reputação do User
* @param name Nome do User
* @param bio Short bio do User
* @param numposts Numero de posts
* @param p array de posts
* @return Cria o Users e as suas informações
*/
Users createUsers(long id, int reputation, char * name,char *bio,int numposts,Post *p) {
    Users u = malloc(sizeof(struct users));
    u->id = id;
    u->reputation = reputation;
    u->name = name;
    u->bio=bio;
    u->numposts=numposts;
    u->lista_posts= p;
    return u;
}


/**
* @brief Faz um shift right ao array de posts
* @param t
* @param ind
* @param numposts
*/
void shiftright(Post *t, int ind, int numposts){
  Post b, a = t[ind];
  int i= ind;
  for(; i <numposts; i++){
    b=t[i+1];
    t[i+1] = a;
    a = b;
  }
}


/**
* @brief Insere um post no array de Post do Users
* @param p
* @param u
*/
void inserePost(Post p, Users u){
DATA pld,pd;

pd=get_CreationDate(p);

  if (u->numposts == 0){
    u->lista_posts =malloc(sizeof(Post));
    u->lista_posts[u->numposts++] = p;
    free_data(pd);
    return;
  }
  u->lista_posts=realloc(u->lista_posts, sizeof(Post)*(u->numposts+1));
  for(int i = 0; i<u->numposts; i++){
      pld=get_CreationDate(u->lista_posts[i]);
   if (comparaDatas(pld,pd) == 2){
      shiftright(u->lista_posts, i, u->numposts);
      u->lista_posts[i] = p;
       u->numposts++;
       free_data(pld);
        free_data(pd);
      return;
    }
    free_data(pld);

  }

  u->lista_posts[u->numposts++] = p;
  free_data(pd);
}


/**
* @brief Procura o id do User
* @param u
* @return retorna o id do User
*/
long get_Uid(Users u) {
    return u->id;
}


/**
* @brief Procura a reputação do User
* @param u
* @return Retorna a reputação do User
*/
int get_Ureputation(Users u) {
    return u->reputation;
}


/**
* @brief Procura o nome do User
* @param u
* @return Retorna o name do User
*/
char * get_Uname(Users u) {
    return  mystrdup(u->name);
}

/**
* @brief Procura a bio do User
* @param u
* @return Retorna a short bio do User
*/
char * get_Ubio(Users u) {
    return mystrdup(u->bio);
}

/**
* @brief Procura a informação relativa ao numero de Post do User
* @param u
* @return Retorna o numposts do User
*/
int get_numpost(Users u){
  return u->numposts;
}



/**
* @brief Faz um clone do array de posts do User
* @param p
* @param numposts
* @return Retorna o clone do array de User
*/
Post* lista_postsclone(Post* p ,int numposts){
    Post* t = malloc(sizeof(Post)*numposts);
    int i;
    for(i=0;i<numposts;i++){
        t[i]=p[i];
    }
    return t;
}


/**
* @brief Procura a lista do array de apontadores para posts
* @param u Users
* @return Retorna a lista do array de apontadores para posts
*/
Post * get_lista_de_posts(Users u) {
    return lista_postsclone(u->lista_posts,u->numposts);
}



/**
* @brief Faz um clone do User que é recebido
* @param a Users
* @return Retorna um clone do User a
*/
Users userclone(Users a){
  Users u = malloc(sizeof(struct users));
    u->id = a->id;
    u->reputation = a->reputation;
    u->name = mystrdup(a->name);
    u->bio= mystrdup(a->bio);
    u->numposts = a->numposts;
    u->lista_posts = lista_postsclone(a->lista_posts,a->numposts);// duvida nesta linha
        return u;
}




/**
* @brief Liberta a memoria alocada para a struct Users 
* @param g Users
*/
void freeuser(Users g){

 free(g->bio);
 free(g->name);
 free(g->lista_posts);
 free(g);
}
