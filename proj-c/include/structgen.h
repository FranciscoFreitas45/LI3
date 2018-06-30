#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <glib.h>

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
#include "list.h"

typedef struct arraygeral *ARRAY;
typedef struct arraygeralDATA *ARRAYD;
typedef struct auxTags *AUXTAGS;



ARRAY creat_ARRAY(int tamanho);
ARRAYD creat_ARRAYD(int tamanho);
int get_tamanho(ARRAY arr);
int get_tamanhoD(ARRAYD arr);
int get_used (ARRAY arr);
int get_usedD(ARRAYD arr);
int* get_array(ARRAY arr);
long *get_arrayP(ARRAY arr);
void set_tamanho(ARRAY arr,int tamanho);
void getNComuns(ARRAYD array1, ARRAYD array2, int N, LONG_list list);
void alloc_long(ARRAY arr,int tamanho);
int verifica_inserido_long(long * arr,int N ,long id);
void insere_ordenado_long (int*arr, long* arrayID ,int N,int x,long id);
void insere(ARRAY v, int x,long id);
int verifica_inserido_DATA(DATA* arr,int N ,DATA id);
void insere_DATA(ARRAYD v,DATA x,long id);
void insere_ordenado_DATA (DATA*arr, long* arrayID ,int N, DATA x,long id);
void printfvalore(ARRAY v);
gboolean runUsers(gpointer key,gpointer value,gpointer data);
gboolean runForCreatReputation (gpointer key, gpointer value, gpointer data);
int minimo(int * arr,int N);
void getNMAX(ARRAY v,int N,int first);
void swapi (int*arr,int max,int first);
void swapl (long*arr,int max,int first);
void inseresimples(ARRAY v,int x,long id);
void incforquery7(ARRAY v, long id);
void free_arraygeral(ARRAY v);
void free_arraygeralDATA(ARRAYD v);

AUXTAGS creat_ARRAY_TAGS(long id, char *name);
void inc_count(AUXTAGS t);
long get_AUXTAGS_id(AUXTAGS t);
char* get_AUXTAGS_name(AUXTAGS t);
int get_AUXTAGS_count(AUXTAGS t);
void merge(int arrl[] ,long arri [], int l, int m, int r);
void mergeSort(ARRAY arr,int l, int r);
void mergeData(DATA arrD[] ,long arrl [], int l, int m, int r);
void mergeSortDATA(ARRAYD arr,int l, int r);
char* concat(const char *path, const char *ficheiro);
char *mystrstr (char s1[], char s2[]);
void free_AUXTAG(AUXTAGS t);



#endif
