#ifndef __LOAD_H_
#define __LOAD_H_

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
#include "avl.h"



gint CompareNames (gconstpointer name1, gconstpointer name2);
gboolean run_Users_forPost(gpointer key,gpointer value, gpointer data);
gboolean traverseTree (gpointer key,gpointer value,gpointer data);
gboolean traverseTreeUsers (gpointer key,gpointer value,gpointer data);
gboolean glibtoAVL(gpointer key,gpointer value,gpointer data);
void parserPost(xmlDocPtr doc,GTree *tree);
void parserUsers(xmlDocPtr doc,GTree *treeUsers);
void parseDoc(char *docname,char * docname2,char*docname3,GTree *tree,GTree *treeUsers,GHashTable *tags);
void freeposts(gpointer data);
void freeusers(gpointer data);
void freetags(gpointer data);
void freeauxtags(gpointer data);



#endif
