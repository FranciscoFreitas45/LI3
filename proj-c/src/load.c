#include <date.h>
#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "owner.h"
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "users.h"
#include "owner.h"
#include "posts.h"
#include "common.h"
#include "load.h"
#include "avl.h"
#include "mytag.h"

/**
* @file load.c
* @author Grupo56
* @date 5 May 2018
*@brief Função que serve para comparar as keys
*@param key1 
*@param key2 
*@return  valor pela a qual irá ser inserida 
*/

gint CompareNames (gconstpointer name1, gconstpointer name2){
		long a1 = *(long *) name1;
		long a2 = *(long *) name2;



		if(a1 > a2)
			 return -1;
		else if (a1 == a2)
			 return 0;
		else return 1;

}

/**
*@brief Função utilizada pelo g_tree_foreach para acabar de preencher as GTrees.
* Na GTree de posts preenche em a struct Owner e na GTree de users insere o post no array dos posts do user. 
*@param key 
*@param Nodo da Gtree de posts 
*@param GTree de users
*@return  valor pela a qual irá ser inserida 
*/



gboolean run_Users_forPost(gpointer key,gpointer value, gpointer data){

	GTree *treeUsers = (GTree *) data;
	Post p =(Post) value;

	long id= get_ownerId(p);

	char *name_owner=NULL;
	long id_owner;
	int reputation_owner;

	Owner o=NULL;

	gpointer g;

	 g=g_tree_lookup(treeUsers,&id);

	 Users u= (Users) g;

	 if(get_typeId(p)<3)
	 inserePost(p,u);
	name_owner=get_Uname(u);
	id_owner=get_Uid(u);
	reputation_owner=get_Ureputation(u);

	o=createOwner(name_owner,id_owner,reputation_owner);

		set_Owner(p,o);
	 return FALSE;
}


/**
*@brief Função que faz o parser da informação do ficheiro Posts.xml para a Gtree de posts
*@param Ficheiro Post.xml 
*@param Gtree de posts 
*/


void parserPost(xmlDocPtr doc,GTree *tree){

	xmlChar *id;
	xmlChar *title;
	xmlChar *typeId;
	xmlChar *ownerId;
	xmlChar * parentId; //
	xmlChar * date;
	xmlChar * tags;
	xmlChar *score;
	xmlChar *commentCount;
	xmlChar *answerCount;


	long keyid;
	short  keytypeId;
	long keyparentId=0;
	int keyscore;
	int keycomentCount;
	int keyanswerCount=0;
	long keyownerId;
	char * titulo;
	char*tag;

	Tags t=NULL;

	Post p =NULL;

	DATA d=NULL;

	xmlNodePtr cur = xmlDocGetRootElement(doc); //<users>
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

	    if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) { //<row

	    	answerCount=(xmlChar*)"0";
	    	parentId =(xmlChar*) "0";

 		    id = xmlGetProp(cur, (const xmlChar *)"Id");   //procura nos atributos o o atributo id e devolve o seu valor;

		    title = xmlGetProp(cur, (const xmlChar *)"Title");

		    typeId = xmlGetProp(cur, (const xmlChar *)"PostTypeId");

		    ownerId = xmlGetProp(cur, (const xmlChar *)"OwnerUserId");

		     date= xmlGetProp(cur, (const xmlChar *)"CreationDate");

		     tags = xmlGetProp(cur, (const xmlChar *)"Tags");

		     score =xmlGetProp(cur, (const xmlChar *)"Score");

		     commentCount=xmlGetProp(cur, (const xmlChar *)"CommentCount");

		     keyid =atoi((char*) id);
		     keytypeId=atoi((char *)typeId);
		     keyparentId=atoi( (char *)parentId);
		     keyscore=atoi((char*)score);
		     keycomentCount=atoi((char*)commentCount);
		     keyownerId=atoi(( char*)ownerId);
		     tag=mystrdup((char*)tags);
		     t=stringToTag_ligada( tag,NULL);

				 free(tag);
		     titulo=mystrdup((char*)title);


/* exceçoes por causa do posttype id*/

		if ((!xmlStrcmp(typeId, (const xmlChar *)"1"))){
				answerCount=xmlGetProp(cur, (const xmlChar *)"AnswerCount");
			keyanswerCount=atoi((char*)answerCount);
			xmlFree(answerCount);
		}
		else if ((!xmlStrcmp(typeId, (const xmlChar *)"2"))){
				parentId=xmlGetProp(cur, (const xmlChar *)"ParentId");
			keyparentId=atoi( (char*)parentId);
			xmlFree(parentId);

}
		d=insereData( (char *)date);

		p =createPost(keyid,titulo,keyownerId,NULL,keytypeId,keyparentId,d,t,keyscore,keycomentCount,keyanswerCount);

		long *keykey=malloc(sizeof(long));
		*keykey= atol((char*) id);
		g_tree_insert(tree,keykey,p);
		xmlFree(title);
		xmlFree(id);
		xmlFree(typeId);
		xmlFree(score);
		xmlFree(commentCount);
		xmlFree(ownerId);
		xmlFree(tags);
		xmlFree(date);


	    }

	    cur = cur->next;
	}


	return;
}

/**
*@brief Função que faz o parser da informação do ficheiro Users.xml para a Gtree de users 
*@param Ficheiro Users.xml 
*@param Gtree de Users 
*/

void parserUsers(xmlDocPtr doc,GTree *treeUsers){

	xmlChar *id;
	xmlChar *reputation;
	xmlChar  *name;
	xmlChar *bio;

	long keyid;
	int keyreputation;
	char* nome;
	char* aboutMe;

	Users u =NULL;

	xmlNodePtr cur = xmlDocGetRootElement(doc); //<users>
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

	    if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) { //<row
 		    id = xmlGetProp(cur, (const xmlChar *)"Id");   //procura nos atributos o o atributo id e devolve o seu valor; 
		  	reputation = xmlGetProp(cur, (const xmlChar *)"Reputation");
		  	name =xmlGetProp(cur,(const xmlChar*) "DisplayName");
		  	bio =xmlGetProp(cur,(const xmlChar *)"AboutMe");
		    keyid =atoi((char*) id);
		    keyreputation=atoi((char *)reputation);
		    nome=mystrdup((char*)name);
		    aboutMe=mystrdup((char*)bio);

		 long *keykey=malloc(sizeof(long));
		*keykey= atol((char*) id);

		u =createUsers(keyid,keyreputation, nome,aboutMe,0,NULL);
		g_tree_insert(treeUsers,keykey,u);

        xmlFree(id);
        xmlFree(reputation);
        xmlFree(name);
        xmlFree(bio);

	    }

	    cur = cur->next;
	}




	return;
}


/**
*@brief Função que faz o parser da informação do ficheiro Tags.xml para a GHashTable 
*@param Ficheiro Tags.xml 
*@param GHashTable de tags 
*/

void parserTags(xmlDocPtr doc,GHashTable *Tags){

	xmlChar *id;
	xmlChar *name;

	long keyid;
	char* nome;
	char * key;
	TAGS t=NULL;

	xmlNodePtr cur = xmlDocGetRootElement(doc); //<users>
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

	    if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) { //<row
 		    	id = xmlGetProp(cur, (const xmlChar *)"Id");   //procura nos atributos o o atributo id e devolve o seu valor;
		  		name = xmlGetProp(cur, (const xmlChar *)"TagName");
				keyid =atol((char*) id);
				nome=mystrdup((char*)name);
				key=mystrdup(nome);
				t=create_tag(keyid,nome);

				g_hash_table_insert(Tags,key,t);
				xmlFree(id);
        		xmlFree(name);


		}

		cur = cur->next;

}
return ;

}



/**
*@brief Função usada no g_tree_foreach que insere na Avl ordenada por data os posts correndo a Gtree dos posts   
*@param Key
*@param Nodo da Gtree de posts
*@param AVL de posts
*@return False para iterar a Gtree até ao fim 
*/


gboolean glibtoAVL(gpointer key,gpointer value,gpointer data){
	Post p =(Post) value;
	AVL* a = (AVL*) data;
	AVL av=NULL;
	av=*a;
	DATA d = get_CreationDate(p);
	av=insertinAVL(d,p,av);
	*a=av;

return FALSE;
}

/**
*@brief Função que invoca as funções parserPost , parserUsers e parserTags
*@param Ficheiro Posts.xml
*@param Ficheiro Users.xml
*@param Ficheiro Tags.xml
*@param Gtree de posts
*@param Gtree de users
*@param GHashTable de tags 
*/





void parseDoc(char *docname,char * docname2,char*docname3,GTree *tree,GTree *treeUsers,GHashTable *tags){

	xmlDocPtr doc,doc2,doc3;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);
	doc2=xmlParseFile(docname2);
	doc3=xmlParseFile(docname3);

	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}

	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}




	parserPost(doc,tree);
	parserUsers(doc2,treeUsers);
	parserTags(doc3,tags);
	xmlFreeDoc(doc);
	xmlFreeDoc(doc2);
	xmlFreeDoc(doc3);
	return;
}

/**
*@brief Função passada como argumento em g_tree_new_full para destruir os posts da Gtree
*@param Post  
*/


	void freeposts(gpointer data){

			Post  p=(Post) data;
			free_post(p);
				}

/**
*@brief Função passada como argumento em g_tree_new_full para destruir os users da Gtree
*@param Users  
*/


void freeusers(gpointer data){
		Users u=(Users) data;
		freeuser(u);
}
/**
*@brief Função passada como argumento em g_hash_table_new_full para destruir as tags da GHashtable
*@param TAGS
*/
void freetags(gpointer data){
		TAGS t=(TAGS) data;
			free_TAG(t);
}
/**
*@brief Função passada como argumento em g_hash_table_new_full para destruir as tags da GHashtable 
*@param AUXTAGS
*/

void freeauxtags(gpointer data){
		AUXTAGS t=(AUXTAGS) data;
			free_AUXTAG(t);
}
