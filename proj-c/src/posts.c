#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "posts.h"
#include "assert.h"
#include "data.h"
#include "common.h"
#include "tag_ligada.h"

/**
* @file posts.c
* @author Grupo56
* @date 5 May 2018
* @brief Struct que guarda um post e toda a sua informacao
*/

	struct post {
		long id;
		char * title;
    long ownerId;
		Owner autor;
		short  typeId;
		long parentId;
		DATA creation_date;
		Tags tag;
		int score;
		int comentCount;
		int answerCount;
 };




/**
* @brief
* @param id id do post
* @param title titulo do post
* @param ownerId id do criador do post
* @param o informações do Owner
* @param typeId se o post é pergunta ou resposta
* @param parentId id do pai do post
* @param d Data
* @param t tags do post
* @param score score do post
* @param comentCount numero de comentarios
* @param answerCount numero de respostas
* @return
*/
Post createPost(long id, char * title,long ownerId, Owner o,short typeId,long parentId, DATA d,Tags t,int score, int comentCount,int answerCount) {

    Post p = malloc(sizeof(struct post));
    p->id =id;
    p->title = title;
    p->ownerId =ownerId;
    p->autor = o;
    p->typeId=typeId;
    p->parentId=parentId;
    p->creation_date=d;
    p->tag =t;
    p->score=score;
    p->comentCount=comentCount;
    p->answerCount=answerCount;
    return p;
}



/**
* @brief Procura o id do Post
* @param p Post
* @return Retorna o id do Post
*/
long get_id(Post p) {
    return p->id;
}


/**
* @brief Procura o titulo do Post
* @param p Post
* @return Retorna o titulo do Post
*/
char * get_title(Post p) {
    return mystrdup (p->title); //change to enum? (Acho que sim. Desta forma já garantimos a limitação necessária)
}


/**
* @brief Procura o id do Owner do Post
* @param p Post
* @return Retorna o ownerId
*/
long get_ownerId(Post p){
    return p->ownerId;
}

/**
* @brief Procura o nome do autor do Post
* @param p Post
* @return Retorna o autor do texto
*/
Owner get_autor(Post p) {
    return p->autor;
}

/**
* @brief Procura o tipo de Post que é,se é pergunta ou resposta
* @param p Post
* @return Retorna o typeId do Post
*/
short get_typeId(Post p) {
    return p->typeId;
}

/**
* @brief Procura o id do pai do Post
* @param p Post
* @return Retorna o parentId
*/
long get_parentId(Post p) {
    return p->parentId;
}

/**
* @brief Procura a data de criazao do post
* @param p Post
* @return Retorna a creationDate
*/
DATA get_CreationDate(Post p) {
    if (!p)return NULL;
    return clone_DATA (p->creation_date);
}

/**
* @brief Procura a lista de tags do Post, clonando para nao se perder informação
* @param p Post
* @return Retorna a lista de tags do post
*/
Tags get_Tags(Post p) {
    return clone_Tags(p->tag);
}

/**
* @brief Procura o score do post
* @param p Post
* @return Retorna o score do Post
*/
int get_score(Post p) {
    return p->score;
}

/**
* @brief Procura o inteiro relativo ao numero de comentarios do post
* @param p Post
* @return Retorna o comentCount do Post
*/
int get_comentCount(Post p){
	return p->comentCount;
}

/**
* @brief Procura o numero de perguntas do post
* @param p Post
* @return Retorna o answerCount do Post
*/
int get_answerCount(Post p){
	return p->answerCount;
}

/**
* @brief Vai ao Owner e retira a string relativa ao nome do autor
* @param p Post
* @return Retorna o nome dentro da struct Owner
*/
char* get_NAME_OwnerPost(Post p){
    return get_Oname(p->autor);
}

/**
* @brief
* @param
* @return 
*/
long get_ID_ownerPost(Post p){
        return get_Oid(p->autor);
}

int get_REPUTACION_ownerPost(Post p){
    return get_Oreputation(p->autor);
}
int get_DATE_DAY_post(Post p){
    return get_data_dia(p->creation_date);
}

int get_DATE_MONTH_post(Post p){
    return get_data_mes(p->creation_date);
}

int get_DATE_YEAR_post(Post p){
    return get_data_ano(p->creation_date);
}



void set_Owner(Post p,Owner o ){
    p->autor=o;
}

long getquestionID(Post p){
    if(p->typeId == 1){
        return p->id;
    }else if (p->typeId == 2){
        return p->parentId;
    }else
    return 0;
}



void free_post(Post p) {
    free(p->title);
    free_owner(p->autor);
    free_tag(p->tag);
    free_data(p->creation_date);
    free(p);
}
