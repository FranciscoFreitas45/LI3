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

typedef struct arraygeral *ARRAY;

ARRAY creat_ARRAY(int tamanho,int used,long*array,long*arrayNPOST);
int get_tamanho(ARRAY arr);
int get_used (ARRAY arr);
long* get_array(ARRAY arr);
long *get_arrayP(ARRAY arr);
void set_tamanho(ARRAY arr,int tamanho);
void alloc(ARRAY arr,int tamanho);
void insere_ordenado (long*arr, long* arrayID ,int N, int x,int id);
void insere(ARRAY v, int x,long id);
void printfvalore(ARRAY v);
gboolean runUsers(gpointer key,gpointer value,gpointer data);
gboolean runUsers_acrescenta(gpointer key,gpointer value,gpointer data);


#endif