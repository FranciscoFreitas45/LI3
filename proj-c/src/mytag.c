#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mytag.h"
#include "common.h"

/**
* @file mytag.c
* @author Grupo56
* @date 5 May 2018
* @brief Guarda o id da tag e uma string com o nome da tag
*/
struct mytags{
    long id;
    char* name;
};

/**
* @brief Recebe o id e o nome da tag e cria uma nova tag
* @param id
* @param name
* @return Return TAGS
*/
TAGS create_tag(long id, char *name){
  TAGS t=malloc(sizeof (struct mytags));
  t->id=id;
  t->name=name;
  return t;
}

/**
* @brief Recebe a tag e procura o id da mesma
* @param t
* @return Retorna o id da tag recebida
*/
long get_tag_id(TAGS t){
  return t->id;
}

/**
* @brief Recebe a tag e procura o nome da mesma, em forma de String
* @param t
* @return o nome da tag
*/
char * get_tag_name(TAGS t ){
  return mystrdup(t->name);
}

/**
* @brief Recebe a tag e o id da tag, e atualiza o id da mesma na struct
* @param t
* @param id
*/
void set_id(TAGS t,long id){
    t->id=id;
}

/**
* @brief Liberta a memoria alocada para a struct TAGS 
* @param t
*/
void free_TAG(TAGS t){
    free(t->name);
    free(t);
}
