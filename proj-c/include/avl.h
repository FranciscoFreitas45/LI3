#ifndef __AVL_H__
#define __AVL_H__
#include "pair.h"
#include "list.h"
#include "structgen.h"

//#define MIN(a,b) (((a)<(b))?(a):(b))
//#define MAX(a,b) (((a)>(b))?(a):(b))


typedef struct myAVL * AVL;
AVL creatNewNode(DATA key ,Post post);
AVL insertinAVL(DATA key,Post post,AVL a);
AVL nextinorder(AVL a);
AVL findFirst(AVL root, DATA minkey);
LONG_list perguntascomtag(AVL a, char* tag, DATA begin, DATA end);
LONG_list maisrespostas(AVL a, int N,DATA begin,DATA end);
LONG_pair get_NUMperguntasRespostas(AVL a, DATA begin, DATA end);
LONG_list melhoresscore(AVL a, int N, DATA begin,DATA end,int tamanho);
LONG_list palavraNoTitulo(AVL a,char *word, int N);
long melhor_resposta(AVL a,DATA begin,long id, int N);
int cotacao(int score,int reputation,int coment);
LONG_list melhorReputacaoComTags(AVL a,int N,int nusers,DATA begin, DATA end, GHashTable *hashtag);
void printintrevalo(AVL a,DATA begin, DATA fim);
void freeAVL(AVL a);
void insere_na_hash(Tags t, GHashTable *tag,GHashTable *hastag);
void passtoStruct(gpointer key,gpointer value,gpointer data);

#endif
