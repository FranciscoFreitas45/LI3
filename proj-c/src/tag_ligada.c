#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tag_ligada.h"
#include "common.h"




/**
* @file tag_ligada.c
* @author Grupo56
* @date 5 May 2018
* @brief Lista ligada de tags
*/
 struct tag_ligadas{
	char * tag;
	struct tag_ligadas *next;
};

/**
* @brief Função que compara se uma tag é igual a outra
* @param tag
* @param tags
* @return se as tags sao iguais ou não
*/
int commontag_compare (char* tag, Tags tags){
	Tags x=tags;
	int flag=1;

	for(;x && flag;x=x->next){
		flag = strcmp(x->tag,tag);
	}
	return !flag ;
}

/**
* @brief Adiciona uma tag à cabeça da lista ligada de tags
* @param string
* @param lista
* @return Retorna a lista ligada de Tags
*/
Tags add_tag (char* string ,Tags lista){
 Tags t = malloc(sizeof(struct tag_ligadas));
 t->tag = string;
 t->next = lista;
 return t;
}

/**
* @brief Parte a string de tags em partes menores, ou seja, em cada tag
* @param str
* @param t
* @return Retorna as Tags
*/
Tags stringToTag_ligada(char* str , Tags t){
int i,a,cont=0;
char* tag;
if (!str) return t;
	for(i=0;str[i]!='\0';i++){
		if(str[i]=='>'){
			tag=malloc((i-cont )*sizeof(char));
			for(a=0;a<(i-cont-1);a++){
				tag[a]=str[a+cont+1];
			}
			tag[a]='\0';
		t=add_tag(tag,t);
		i++;
		cont=i;
  }
  }


	return t;
}


/**
* @brief Liberta a memoria alocada para as Tags, lista ligada e apontador para a proxima
* @param t
*/
void free_tag(Tags t){
Tags a;
  while(t){
    free(t->tag);
    a=t->next;
    free(t);
    t=a;
  }

}


/**
* @brief Faz um clone da lista ligada para não se perder informação
* @param t
* @return Retorna as Tags
*/
Tags clone_Tags(Tags l){
    Tags ret=NULL;
    Tags nova, aux2 = NULL;
    while(l){
        nova=(Tags)malloc(sizeof(struct tag_ligadas));
        if(!ret) ret = nova;
        if(aux2) aux2->next = nova;
        nova->tag=mystrdup(l->tag);
        nova->next = NULL;
        aux2 = nova;
        l=l->next;
    }
    return ret;
}

/**
* @brief Retorna o nome da tag da lista de Tags
* @param t
* @return Retorna o nome da tag
*/
char* get_tag_ligada(Tags t){
    if(!t)
      return NULL;
   else return mystrdup(t->tag);
}

/**
* @brief Percorre a lista ligada 
* @param t
* @return Retorna o apontador para a proxima posição da lista ligada
*/
Tags proximo(Tags t){
  return (t->next);

}
