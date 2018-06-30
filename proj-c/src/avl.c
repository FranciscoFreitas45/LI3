#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"
#include "posts.h"
#include "avl.h"
#include <string.h>
#include "load.h"
#include "tag_ligada.h"
#include "mytag.h"
#include "structgen.h"


/**
 * @file avl.c
 * @author Grupo56
 * @date 5 May 2018
 * @brief myAVL Arvore binaria de post
 * @param altura altura da AVL
 * @param *dir apontador para a direita da AVL
 * @param *esq apontador para a esquerda da AVL
 * @param *pai apontador para o pai do nodo
 * @param key chave de data pela qual a AVL vai ser ordenada
 * @param numposts numero de posts que o nodo contem
 * @param lista_posts apontador para o array de post
 * @param isleft se for 1,o nodo e a esquerda do seu pai, se for 0, e a direita,e se for -1, e a raiz da AVL
 */
struct myAVL{
    int altura;
    struct myAVL *dir, *esq;
    struct myAVL *pai;
    DATA key;
    int numposts;
    Post* lista_posts;
    int isleft;
};

/**
 * @brief [getaltura Funcao que calcula a altura da AVL]
 * @param  a [AVL]
 * @return   [Altura da AVL]
 */
int getaltura(AVL a) {
    if (a)
        return a->altura;
    return -1;
}

/**
 * @brief [creatNewNode Cria um nodo novo na AVL]
 * @param  key  [data de ordenacao]
 * @param  post [post]
 * @return      [AVL com o novo novo inserido]
 */
AVL creatNewNode(DATA key ,Post post){

    AVL node;
    node = malloc(sizeof(struct myAVL));
    node->altura = 0;
    node->esq = NULL;
    node->dir = NULL;
    node->pai = NULL;
    node->key = key;
    node->numposts=1;
    node->lista_posts = malloc(sizeof(Post));
    *(node->lista_posts)= post;
    node->isleft = -1;

    return node;
}

/**
 * @brief Funcao que insere o novo post no array de posts
 * @param a AVL
 * @param b Post que ira ser inserido
 */
void inserenodo(AVL a,Post b){
  if(!a){
    return;
  }
  a->numposts++;
  a->lista_posts= realloc(a->lista_posts, sizeof(Post)*(a->numposts));
  a->lista_posts[(a->numposts)-1]=b;
return;
}



/**
* @brief Faz a rotacao a direita da AVL quando esta nao esta balanceada
* @param a AVL
* @return AVL rodada para a direita
*/
AVL rotateright(AVL a){
    AVL aux;
    int b = a->isleft;
    AVL c = a->pai;
    aux=a->esq;
    a->esq=aux->dir;
    aux->dir=a;
    aux->pai = a->pai;
    aux->isleft = a->isleft;
    a->isleft=0;
    a->pai=aux;
    a->altura=MAX(getaltura(a->dir)+1,getaltura(a->esq)+1);;
    if(a->esq) {
        a->esq->pai = a;
        a->esq->isleft = 1;
    }
    aux->altura= MAX(getaltura(aux->dir)+1,getaltura(aux->esq)+1);
    if(c){
      if(b){
        c->esq=aux;
      }else{
        c->dir=aux;
      }
    }
    return aux;
}

/**
* @brief Roda a AVL para a esquerda quando esta nao esta balanceada
* @param a AVL
* @return AVL depois derodada para a esquerda
*/
AVL rotateleft(AVL a){
    AVL aux;
    int b = a->isleft;
    AVL c = a->pai;
    aux=a->dir;
    a->dir=aux->esq;
    aux->esq=a;
    aux->pai = a->pai;
    aux->isleft = a->isleft;
    a->pai=aux;
    a->isleft=1;
    a->altura=MAX(getaltura(a->dir)+1,getaltura(a->esq)+1);
    if(a->dir) {
        a->dir->pai = a;
        a->dir->isleft=0;
    }
    aux->altura= MAX(getaltura(aux->dir)+1,getaltura(aux->esq)+1);
    if(c){
      if(b){
        c->esq=aux;
      }else{
        c->dir=aux;
      }
    }
    return aux;
}

/**
* @brief Calcula o factor de balanceamento da AVL
* @param a AVL
* @return Factor que diz se a AVL esta balanceada ou nao, e para que lado nao esta
*/
int getbalanceFactor(AVL a){
  if(!a)
  return 0;
  return getaltura(a->esq) - getaltura(a->dir);
}

/**
* @brief Funcao que de acordo com o desbalanceamento da arvore, balanceia a AVL
* @param a AVL
* @return AVL depois de balanceada
*/
AVL balance(AVL a){
  AVL c=a;
    int bal = getbalanceFactor(a);
    int b;
    if(bal == 2){
        b=getbalanceFactor(c->esq);
        if(b==-1)
        c->esq = rotateleft(c->esq);
        c = rotateright(c);
    }else if(bal == -2){
            b=getbalanceFactor(c->dir);
            if(b==1)
            c->dir = rotateright(c->dir);
            c = rotateleft(c);
        }
    return c;
}

/**
* @brief Funcao que insere um novo nodo na AVL, e se o nodo ja existir, insere
* ordenadamente no array de posts,de acordo com a key
* @param key data para inserir na AVL
* @param post post que ira ser inserido na AVL
* @param a AVL
* @return AVL com o novo post inserido, de acordo com a key
*/
AVL insertinAVL(DATA key,Post post,AVL a){
    AVL b=a;
    AVL cur;

    while (1){
        if(!a){
             b = creatNewNode( key, post);
            break;
        }else if((comparaDatas(key,b->key))==1){
            if(b->dir){
                b=b->dir;
              }
            else{
                cur= malloc(sizeof(struct myAVL));
                cur->key= key;
                cur->altura=0;
                cur->esq=NULL;
                cur->dir=NULL;
                cur->pai=b;
                cur->isleft=0;
                cur->numposts=1;
                cur->lista_posts = malloc(sizeof(Post));
                *(cur->lista_posts)= post;
                b->dir=cur;
                break;
            }
        }else if((comparaDatas(key,b->key))==2){
            if(b->esq){
                b=b->esq;
              }
            else{
                cur= malloc(sizeof(struct myAVL));
                cur->key= key;
                cur->altura=0;
                cur->esq=NULL;
                cur->dir=NULL;
                cur->pai=b;
                cur->isleft=1;
                cur->numposts=1;
                cur->lista_posts = malloc(sizeof(Post));
                *(cur->lista_posts)= post;
                b->esq=cur;
                break;
            }
        }else{
            inserenodo(b,post);
            break;
        }
    }
    while(1){
        b->altura= MAX(getaltura(b->dir)+1,getaltura(b->esq)+1);
        b = balance(b);
        if(b->pai){
          b=b->pai;
        }else
            break;
    }
    return b;

}

/**
* @brief Calcula o nodo mais a direita, maior nodo da AVL
* @param a AVL
* @return Nodo mais a direita da AVL, ou raiz quando nao ha direita
*/
AVL maxvalue(AVL a){
    AVL b = a;
    if(!b) {
      return NULL;
    }
    for(;b->dir;b=b->dir);
    return b;
}

/**
* @brief Calcula o nodo mais a esqueda, menor nodo da AVL
* @param a AVL
* @return Nodo mais a esquerda da AVL, ou raiz quando nao ha esquerda
*/
AVL minvalue(AVL a){
    AVL b = a;
    if (!b) {
      return NULL;
    }
    for(;b->esq;b=b->esq);
    return b;
}

/**
* @brief Calcula o nodo que esta anteriormente em ordem
* @param a Nodo da AVL
* @return Nodo anteriormente em ordem
*/
AVL previousinOrder(AVL a){
    AVL b=a;
    if (b->esq) {
        return maxvalue(b->esq);
    } else {
        while(1) {
            if (b->pai) {
                if (!(b->isleft))
                    return b->pai;
                else b = b->pai;
            }else {
                return NULL;
            }
        }
    }
}

/**
* @brief Calcula o nodo ordenado, logo a seguir ao nodo dado
* @param a Nodo da AVL
* @return Nodo logo a seguir em ordem
*/
AVL nextinorder(AVL a){
    AVL b=a;
    if (b->dir) {
        return minvalue(b->dir);
    } else {
        while(1) {
            if (b->pai) {
                if (b->isleft)
                    return b->pai;
                else b = b->pai;
            }else {
                return NULL;
            }
        }
    }
}

/**
* @brief Procura a data do primeiro post com a key na AVL, se existir devolve o nodo,
* senao procura no resto da arvore se existe de acordo com a ordenacao das datas.
* @param root Raiz da arvore
* @param minkey Data passada como argumento
* @return Nodo com aquela key, e se nao encontrar nenhum com aquela data na Arvore
* retorna o nextinOrder
*/
AVL findFirst(AVL root, DATA minkey){
    AVL a = root;
    if(!a)
    return NULL;
    while(1){
    if((comparaDatas(minkey,a->key))==2){
        if(a->esq)
            a=a->esq;
        else return a;
      }else if((comparaDatas(minkey,a->key))==1){
        if(a->dir)
            a=a->dir;
        else return nextinorder(a);
    }else{
        return a;
    }
  }
}

/**
* @brief Procura o ultimo nodo com uma certa key, e se encontrar, devolve o nodo,
* senao, procura no resto da arvore de acordo com a ordenacao por datas da AVL
* @param root Raiz da arvore
* @param maxkey Data passada como argumento
* @return Nodo com a key, e se nao encontrar nenhum, devolve o previousinOrder
*/
AVL findLast(AVL root, DATA maxkey){
    AVL a = root;
    if(!a)
    return NULL;
    while(1){
    if((comparaDatas(maxkey,a->key))==2){
        if(a->esq)
            a=a->esq;
        else return previousinOrder(a);
      }else if((comparaDatas(maxkey,a->key))==1){
        if(a->dir)
            a=a->dir;
        else return a;
    }else{
        return a;
    }
  }
}

/**
* @brief Verifica se a AVL esta balanceada (usando a funcao que o fator de
* balanceamento)
* @return 1 se o fator de balanceamento for maior que 1 ou menor que -1, e
* retorna 0 se o fator de balanceamento for igual a 1 ou -1
*/
int isbalanced(AVL a){
  int b = getbalanceFactor(a);
  if (b<-1 || b>1)
  return 0;
  return 1;
}

/**
* @brief Calcula a altura da arvore recursivamente, mais usada para testes
* @param a AVL
* @return Altura da AVL
*/
int getalturaR(AVL a){
  if(!a)
  return -1;
  return (MAX((getalturaR(a->dir)+1),(getalturaR(a->esq)+1)));
}

/**
* @brief Verifica recursivamente se a AVL esta balanceada, tambem para testes
* @param a AVL
* @return Retorna se a AVL esta balanceada ou nao
*/
int isbalancedR(AVL a){
  if (!a)
  return 1;
  int b = (getalturaR (a->esq))-(getalturaR(a->dir));
  int c = (b>-2 && b <2);
  return (c && isbalancedR(a->esq) && isbalancedR(a->dir));
}

/**
* @brief Verifica se os apontadores da arvore estao corretos, tambem de teste
* @param a AVL
* @return Retorna se os apontadores da AVL estao corretos ou nao
*/
int areALLpointeresOK(AVL a){
  int b,c;
  if(!a)
  return 1;
  if(a->dir){
    b=((a->dir->pai==a) && (a->dir->isleft == 0));
  }
  if(a->esq){
    c=((a->esq->pai==a) && (a->esq->isleft == 1));
  }
  return (c && b && (areALLpointeresOK(a->dir)) && (areALLpointeresOK(a->esq)));
}

/**
* @brief
* @param h
* @return
*/
int calcpossiblenodes(int h){
  int a=0;
  int c=1;
  int i;
  int b;
  for(i=h;i>=0;i--){
    for(b=i;b>0;b--){
      c=c*2;
    }
    a+=c;
    c=1;
  }
  return a;
}

/**
* @brief Calcula o numero de respostas e perguntas dentro de uma certa data,
* fazendo a comparacao entre os typeID
* @param a AVL
* @param begin Data passada como argumento
* @param end Segunda data passada como argumento
* @return Retorna um LONG_pair, com o numero de respostas, e o numero de perguntas
*/
LONG_pair get_NUMperguntasRespostas(AVL a, DATA begin, DATA end){
  AVL b= findFirst(a, begin);
  LONG_pair pair;
  int i,typeID;
  long fst=0,snd=0;
  for(;b && (comparaDatas(b->key,end)==2 || comparaDatas(b->key,end)==0) ;b=nextinorder(b)){
      for(i=0;i<b->numposts;i++){
      typeID = get_typeId(b->lista_posts[i]);
      if(typeID==1)
      fst++;
      else if(typeID==2)
      snd++;

      }
}
pair=create_long_pair(fst,snd);
return pair;
}

/**
* @brief Corre o intervalo de tempo, e procura em todas as perguntas, se tem
* a tag passada como argumento
* @param a AVL
* @param tag
* @param begin Data passada como argumento
* @param end Segunda data passada como argumento
* @return Retorna uma LONG_list
*/
LONG_list perguntascomtag(AVL a, char* tag, DATA begin, DATA end){
  AVL b= findLast(a, end);
  LONG_list finallist;
  int i,size=0;
  long* list=NULL;
  for(;b && (comparaDatas(b->key,begin)==1 || comparaDatas(b->key,begin)==0) ;b=previousinOrder(b)){
      for(i=0;i<b->numposts;i++){
        if(get_typeId(b->lista_posts[i])==1){
          Tags tt = get_Tags(b->lista_posts[i]);
                   if(commontag_compare(tag,tt)){
                     list=realloc(list,(size+1)*(sizeof (long)));
                     list[size]=get_id(b->lista_posts[i]);
                     size++;
                     }
                     free_tag(tt);
              }
            }
      }
    finallist = create_list(size);


    for(i=0;i<size;i++){
      set_list(finallist,i,list[i]);
    }
    free(list);
    return finallist;
}

/**
* @brief Procura neste intervalo,as N respostas com mais score
* @param a AVL
* @param N
* @param begin Data passada como argumento
* @param end Segunda data passada como argumento
* @param tamanho
* @return Retorna um LONG_list
*/
LONG_list melhoresscore(AVL a, int N, DATA begin,DATA end,int tamanho){
    ARRAY arr=creat_ARRAY(tamanho);//crio a struct com os dois array
    AVL b= findFirst(a, begin);
    LONG_list finallist;
    long * ids;
    int i;
    int conta;
    for(;b && (comparaDatas(b->key,end)==2 || comparaDatas(b->key,end)==0) ;b=nextinorder(b)){
        for(i=0;i<b->numposts;i++){
            if(get_typeId(b->lista_posts[i])==2)
          insere(arr,get_score(b->lista_posts[i]),get_id (b->lista_posts[i]));
        }
      }
      mergeSort(arr,0,get_used(arr)-1);
      conta=get_used(arr);
      finallist=create_list(N);
       ids=get_arrayP(arr);
        if(get_used(arr)<N)
          conta =get_used(arr);
        else conta=N;

      for(i=0;i<conta;i++){
        set_list(finallist,i,ids[i]);
      }
      if(conta<N)
      for(;conta<N;conta++){
        set_list(finallist,conta,-1);
      }
      free_arraygeral(arr);
return finallist;

}

/**
* @brief Procura neste intervalo,as N perguntas com mais respostas
* @param a AVL
* @param N
* @param begin Data passada como argumento
* @param end Segunda data passada como argumento
* @return Retorna LONG_list
*/
LONG_list maisrespostas(AVL a, int N,DATA begin,DATA end ){
  ARRAY arr=creat_ARRAY(N);//crio a struct com os dois array
  AVL b= findFirst(a, begin);
  LONG_list finallist;
  long * ids;
  int i;
  int conta;
  for(;b && (comparaDatas(b->key,end)==2 || comparaDatas(b->key,end)==0) ;b=nextinorder(b)){
      for(i=0;i<b->numposts;i++){
          if(get_typeId(b->lista_posts[i])==1)
               inseresimples(arr,0,get_id(b->lista_posts[i]));
          else if (get_typeId(b->lista_posts[i])==2)
               incforquery7(arr,get_parentId(b->lista_posts[i]));
           }
      }
    getNMAX(arr, N , 0);
    if(get_used(arr)<N){
    conta=get_used(arr);
  }
  else{
  conta = N;
}
    finallist=create_list(N);
     ids=get_arrayP(arr);
    for(i=0;i<conta;i++){
      set_list(finallist,i,ids[i]);

    }
    if(conta<N)
    for(;conta<N;conta++){
      set_list(finallist,conta,-1);
    }
    free_arraygeral(arr);
return finallist;

}

/**
* @brief Verifica se uma certa palavra esta no titulo da pergunta
* @param a AVL
* @param word Palavra que ira ser procurada no titulo
* @param N
* @return Retorna LONG_list
*/
LONG_list palavraNoTitulo(AVL a,char * word, int N){
    AVL b= maxvalue(a);
    LONG_list finallist;
    int i;
    long list[N];
    int size=0;
    for(;b &&  size<N  ;b=previousinOrder(b)){
        for(i=0;i<b->numposts;i++){
          if(get_typeId(b->lista_posts[i])==1 && size<N ){
              char* title=get_title(b->lista_posts[i]);
                     if(strstr(title,word)){
                       list[size]=get_id(b->lista_posts[i]);
                       size++;
                    }
                  free(title);
               }
              }
        }
      finallist = create_list(N);

      for(i=0;i<size;i++){
        set_list(finallist,i,list[i]);
      }

        for(;size<N;size++)
          set_list(finallist,size,-1);


return finallist;
}

/**
* @brief Calcula a cotacao da resposta
* @param score
* @param reputation
* @param coment
* @return Retorna a cotacao calculada
*/
int cotacao(int score,int reputation,int coment){
  int x= (0.65*score+0.25*reputation+0.1*coment);
  return x;
}

/**
* @brief Calcula a resposta com melhor cotacao
* @param a AVL
* @param begin Data dada por argumento(criacao da pergunta)
* @param end Segunda data dada como argumento
* @param N numero de respostas que a pergunta tem
* @return Resposta com melhor cotacao
*/
long melhor_resposta(AVL a,DATA begin,long id, int N){
AVL b= findFirst(a, begin);
  int i,conta;
  int resultado=0;
  int x=0;
  long idResposta=-1;
  for(conta=0;b && conta<N ;b=nextinorder(b)){
      for(i=0;i<b->numposts;i++){
          if(get_typeId(b->lista_posts[i])==2)// se for resposta
            if(get_parentId(b->lista_posts[i])==id){// se for resposta á pergunta
                x=cotacao(get_score(b->lista_posts[i]),get_REPUTACION_ownerPost(b->lista_posts[i]),get_comentCount(b->lista_posts[i]));
                if (x>resultado){
                  idResposta=get_id(b->lista_posts[i]);
                  resultado=x;
                  conta++;
                }
            }

      }
    }
    return idResposta;
}



/**
* @brief Passa o valor de cada nodo da Hash table para a struct auxiliar ARRAY
* @param key
* @param value
* @param data
*/
void passtoStruct(gpointer key,gpointer value,gpointer data){

    ARRAY arr = (ARRAY) data;

    AUXTAGS t = (AUXTAGS) value;

    int count=get_AUXTAGS_count(t);
    long id =get_AUXTAGS_id(t);
      insere(arr,count,id);
}

/**
* @brief Insere na hash table auxiliar o nome da tag, ou se ja existir, incrementa a
* contagem dessa tag
* @param t Lista ligada de Tags
* @param tag hash table auxiliar
* @param hastag
*/
void insere_na_hash(Tags t, GHashTable *tag,GHashTable *hastag){

    Tags aux=t;
  AUXTAGS tt;
  while(aux){
        char* name =get_tag_ligada(aux);
          if (!name)  printf("merda\n" );
            gpointer gg=g_hash_table_lookup(hastag,name);//ir á struct das tags que tem nome e id dela
              if (gg){// se existir
                TAGS nodo= (TAGS) gg;
                long id = get_tag_id(nodo);
            gpointer g=g_hash_table_lookup(tag,name);//procura na hash auxiliar
              if(g){
             tt=(AUXTAGS)g;
            inc_count(tt);
            free(name);
             }

else {
  AUXTAGS ttT =creat_ARRAY_TAGS(id, name);
  g_hash_table_insert(tag,name,ttT);
}
              }
aux=proximo(aux);
}
}


/**
* @brief Calcula os N users com mais reputacao e as N tags mais usadas por eles
* @param a AVL
* @param N
* @param nusers
* @param begin
* @param end
* @param hashtag
* @return Retorna uma LONG_list
*/
LONG_list melhorReputacaoComTags(AVL a,int N,int nusers,DATA begin, DATA end, GHashTable *hashtag){
//ir buscar os gajos com mais reputaçao no intervalo dado
AVL c=findFirst(a,begin);
ARRAY mais_reputacao=creat_ARRAY(nusers);
long id;
int reputacion;
int i;
LONG_list finallist=create_list(N);
GHashTable *tag=g_hash_table_new_full((GHashFunc)&g_str_hash,&g_str_equal,&free,&freeauxtags);

  for(;c && (comparaDatas(c->key,end)==2 || comparaDatas(c->key,end)==0) ;c=nextinorder(c)){
      for(i=0;i<c->numposts;i++){
              id=get_ownerId(c->lista_posts[i]);
              reputacion= get_REPUTACION_ownerPost(c->lista_posts[i]);
            if(!verifica_inserido_long(get_arrayP(mais_reputacao),get_used(mais_reputacao),id)){
                insere(mais_reputacao,reputacion,id);
              }
}
}
  mergeSort(mais_reputacao,0,get_used(mais_reputacao)-1);

  // responder propriamente á query
  //ir buscar so o array dos ids;
  long * maior_reputacao=get_arrayP(mais_reputacao);

//passar para um array os N gajos com mais reputaçao;
  long * grt_rep= malloc(N *sizeof(long));
  memcpy(grt_rep, maior_reputacao, sizeof(long) * N);


  ARRAY q11;
  q11=creat_ARRAY(nusers);
  long *count;
  int conta=0;
  Tags t=NULL;
  AVL b= findFirst(a, begin);
  for(;b && (comparaDatas(b->key,end)==2 || comparaDatas(b->key,end)==0) ;b=nextinorder(b)){
      for(i=0;i<b->numposts;i++){
          if(verifica_inserido_long(grt_rep,N,get_ownerId(b->lista_posts[i]))){
            t=(get_Tags(b->lista_posts[i]));
      insere_na_hash(t,tag,hashtag);
        conta++;
          free_tag(t);
          }
        }
  }
g_hash_table_foreach(tag, &(passtoStruct),q11);
mergeSort(q11,0,get_used(q11)-1);
count=get_arrayP(q11);

for(i=0;i<N;i++){
  set_list(finallist,i,count[i]);
}

g_hash_table_destroy(tag);
free_arraygeral(q11);
free_arraygeral(mais_reputacao);
free(grt_rep);

return finallist;
}


/**
* @brief Liberta a memoria alocada pela AVL
* @param a AVL
*/
void freeAVL(AVL a){

   if(a->dir)
   freeAVL(a->dir);
   if(a->esq){
     freeAVL(a->esq);
   }
   free(a->lista_posts);
   free_data(a->key);
   free(a);
}
