#include "users.h"
#include "owner.h"
#include "posts.h"
#include <date.h>
#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "load.h"
#include "data.h"
#include "avl.h"
#include "structgen.h"


/**
* @file interface.c
* @author Grupo56
* @date 5 May 2018
* @brief Tipo contreto de dados
*/
struct TCD_community{
	GTree	*treeusers;
	GTree	*treepostsid;
	ARRAY  arrNpost;
	AVL AVLpostDatas;
	GHashTable *tags;
};

/**
* @brief Inicializa a nossa struct geral do trabalho
* @return TAD_community
*/
TAD_community init(){
	TAD_community com=malloc(sizeof(struct TCD_community));
	com->treepostsid=g_tree_new_full((GCompareDataFunc) &CompareNames,NULL,&free,&freeposts);
	com->treeusers=g_tree_new_full((GCompareDataFunc) &CompareNames,NULL,&free,&freeusers);
	com->arrNpost=NULL;
	com->AVLpostDatas=NULL;
  com->tags=g_hash_table_new_full((GHashFunc )&g_str_hash,g_str_equal,&free,&freetags);

	return com;
}

/**
* @brief Carrega a nossa struct
* @param com Struct que sera carregada
* @param path Caminho para os ficheiros
* @return TAD_community
*/
TAD_community load(TAD_community com,char* path) {

int count;
char* docname1=concat(path,"Posts.xml");
char *docname2=concat(path,"Users.xml");
char*docname3=concat(path,"Tags.xml");


parseDoc(docname1,docname2,docname3,com->treepostsid,com->treeusers,com->tags);
	//parseDoc(docname,docname2,com->treepostsid,com->treeusers,&(com->AVLpostDatas));

	g_tree_foreach(com->treepostsid,&(run_Users_forPost),com->treeusers);

	g_tree_foreach(com->treepostsid,&(glibtoAVL),&(com->AVLpostDatas));
  count= g_tree_nnodes (com->treeusers);

  com->arrNpost=creat_ARRAY(count);


	g_tree_foreach(com->treeusers,&(runUsers),com->arrNpost);

mergeSort(com->arrNpost,0,count-1);
free(docname1);
free(docname2);
free(docname3);
return com;


}

/**
* @brief Dado um id de um post, ve a informacao relativa ao post(titulo do post)
* e nome de utilizador do autor
* @param com
* @param id do post
* @return STR_pair
*/
STR_pair info_from_post(TAD_community com, long id){


	char* titulo;
	char *nome;
	STR_pair information=NULL;

		gpointer g= g_tree_lookup(com->treepostsid,&id);
			Post p= (Post ) g;

			if(get_typeId(p)==2)
			{
				long *pai=malloc(sizeof (long));
				*pai=get_parentId(p);

				gpointer gg=g_tree_lookup(com->treepostsid,pai);
				Post pp=(Post) gg;
				nome=get_NAME_OwnerPost(pp);
				titulo=get_title(pp);
				information =create_str_pair(titulo,nome);
				printf("%s\n",nome);
				printf("%s\n",titulo);
				return information;
			}

				nome=get_NAME_OwnerPost(p);
				titulo=get_title(p);
				information =create_str_pair(titulo,nome);
				free(nome);
				free(titulo);
				return information;
}


/**
* @brief De acordo com o intervalo de tempo dado, calcula numero total de posts
* dentro da data, identificando perguntas e respostas
* @param com
* @param begin
* @param end
* @return Retorna um LONG_pair
*/
LONG_pair total_posts(TAD_community com, Date begin, Date end){
	DATA data1 = dateTodata(begin);
	DATA data2 =dateTodata(end);
	LONG_pair result = get_NUMperguntasRespostas(com->AVLpostDatas, dateTodata(begin), dateTodata(end));
	free_data(data1);
	free_data(data2);
	return result;
}

/**
* @brief De acordo com a data dada,calcula todas as perguntas que contem uma certa tag
* ordenando por ondem cronologica inversa
* @param com
* @param tag
* @param begin
* @param end
* @return Retorna uma LONG_list
*/
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
 DATA data1 = dateTodata(begin);
 DATA data2 =dateTodata(end);
 LONG_list result = perguntascomtag(com->AVLpostDatas,tag,data1, data2);
 free_data(data1);
 free_data(data2);
 return result;
}


/**
* @brief Calcula os IDS das N perguntas com mais respostas, dentro de um certo
* intervalo de tempo
* @param com
* @param N
* @param begin
* @param end
* @return Retorna um LONG_list
*/
LONG_list most_answered_questions(TAD_community com,int N, Date begin, Date end){
	DATA data1 = dateTodata(begin);
  DATA data2 =dateTodata(end);
  LONG_list result = maisrespostas(com->AVLpostDatas,N,data1, data2);
	free_data(data1);
	free_data(data2);
	return result;
}

/**
* @brief Com o ID de um autor, retira a informacao da short bio dele, e os IDS
* dos ultimos 10 posts efetuados por ele
* @param com
* @param id
* @return Retorna um USER
*/
USER get_user_info(TAD_community com, long id){

	int i,a=10;
	char *bio;

		USER info =NULL;
		gpointer g= g_tree_lookup(com->treeusers,&id);
			Users u= (Users ) g;

			bio=get_Ubio(u);
		Post *p=NULL;

		p= get_lista_de_posts(u);

		long array[10];
    	if(get_numpost(u)<10)
        a=get_numpost(u);
		for(i=0;i<a;i++){
			long id =get_id(p[i]);
			array[i]=id;
		}

		if(get_numpost(u)<10)
		{
		for(;a<10;a++)
				array[a]=-1;

	}

		info =create_user(bio,array) ;
		free(p);

		return info;

}

/**
* @brief Dentro de um certo intervalo de tempo devolver as N perguntas com mais
* votos, em ordem decrescente do numero de votos
* @param com
* @param N
* @param begin
* @param end
* @return Retorna um LONG_list
*/
LONG_list most_voted_answers(TAD_community com,int N, Date begin, Date end){
	DATA data1 = dateTodata(begin);

  DATA data2 =dateTodata(end);
	int nnodos= g_tree_nnodes (com->treepostsid);
	LONG_list result = melhoresscore(com->AVLpostDatas,N,data1, data2,nnodos);
	free(data1);
	free(data2);
	return result;
}

/**
* @brief Dado uma palavra, dar os IDS das N perguntas que contenham a palavra
* dada (word)
* @param com
* @param word
* @param N
* @return Retorna um LONG_list
*/
LONG_list contains_word(TAD_community com,char *word,int N){
  return palavraNoTitulo(com->AVLpostDatas,word,N);
}
long better_answer(TAD_community com, long id){
	long resposta=-1;
  gpointer g=g_tree_lookup(com->treepostsid,&id);
    if(g){
      Post p=(Post) g;
      DATA d =get_CreationDate(p);
      int answer=get_answerCount(p);
      if(answer!=0)
				resposta=melhor_resposta(com->AVLpostDatas,d,id,answer);
  		free_data(d);
			return resposta;
    }
   return -1;
}

/**
* @brief Obtem os N utilizadores com mais atividade de sempre, ou seja, com maior
* numero de posts de sempre, sendo consideradas tanto perguntas como respostas
* @param com
* @param N
* @return Retorna um LONG_list
*/
LONG_list top_most_active(TAD_community com, int N){

	int i=0;
	LONG_list l =create_list( N);


       	long *arr= get_arrayP(com->arrNpost);
       	for(i=0;i<N;i++)
			set_list(l,i,arr[i]);
		return l;

}


/**
* @brief Dado os IDS de dois utilizadores, devolver as ultimas N perguntas em
* que ambos participaram, via pergunta ou resposta, por ordem cronologica inversa
* @param com
* @param id1
* @param id2
* @param N
* @return Retorna um LONG_list
*/
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
 long* ID1 = malloc(sizeof (long));
 long* ID2 = malloc(sizeof (long));
 LONG_list list = create_list(N);
 *ID1=id1;
 *ID2=id2;
 int i;
 int numpost1;
 int numpost2;
 Post* posts1;
 Post* posts2;
 Post cur;
 gpointer g;
 Users user1 = (Users) g_tree_lookup(com->treeusers,&id1);
 Users user2 = (Users) g_tree_lookup(com->treeusers,&id2);
  if(user1 && user2){
    numpost1 = get_numpost(user1);
    numpost2 = get_numpost(user2);
    posts1 = get_lista_de_posts(user1);
    posts2 = get_lista_de_posts(user2);
	}else{
    return NULL;
  }
  ARRAYD arr1 = creat_ARRAYD(numpost1);
  ARRAYD arr2 = creat_ARRAYD(numpost2);
 for(i=0; i < numpost1; i++){

   long*ID3= malloc(sizeof(long));

    *ID3= getquestionID(posts1[i]);
   if(*ID3 && com->treepostsid){
     g = g_tree_lookup(com->treepostsid,(gconstpointer) ID3);
     cur=g;
   if(cur){
     insere_DATA(arr1, get_CreationDate(cur), *ID3);
  }
 }
 	free(ID3);
 }
mergeSortDATA(arr1,0,get_usedD(arr1)-1);

 for(i=0; i < numpost2; i++){
	 long*ID4= malloc(sizeof(long));

	  *ID4= getquestionID(posts2[i]);


   if(*ID4 && com->treepostsid){
		 g = g_tree_lookup(com->treepostsid,(gconstpointer) ID4);
     cur=g;
   if(cur){
     insere_DATA(arr2, get_CreationDate(cur), *ID4);

	}
 }
 free(ID4);
 }



mergeSortDATA(arr2,0,get_usedD(arr2)-1);

 getNComuns(arr1,arr2,N,list);
 free(ID1);
 free(ID2);
 free(posts1);
 free(posts2);
 free_arraygeralDATA(arr1);
 free_arraygeralDATA(arr2);
 return list;

}

/**
* @brief Dentro de um dado intervalo de tempo, devolve as N tags mais usadas
* pelos N utilizadores com melhor reputacao, por ordem decrescente do numero
* de vezes em que a tag e utilizada
* @param com
* @param N
* @param begin
* @param end
* @return Retorna um LONG_list
*/
LONG_list most_used_best_rep(TAD_community com, int N, Date begin,Date end){
	DATA data1 = dateTodata(begin);

  DATA data2 =dateTodata(end);
	int nusers =g_tree_nnodes(com->treeusers);

  LONG_list result = melhorReputacaoComTags(com->AVLpostDatas,N,nusers,data1,data2,com->tags);
	free_data(data1);
	free_data(data2);
	return result;




}



/**
* @brief Liberta a memoria alocada para a TAD_community
* @param com
* @return Retorna TAD_community
*/
TAD_community clean(TAD_community com){

  g_hash_table_destroy(com->tags);
	g_tree_destroy(com->treepostsid);
	g_tree_destroy(com->treeusers);
	freeAVL(com->AVLpostDatas);

	free_arraygeral(com->arrNpost);
return com;
}
