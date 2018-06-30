#ifndef __POSTLIGADO__
#define __POSTLIGADO__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "posts.h"
#include "assert.h"

typedef struct post_ligado * LPOST;

LPOST createLPost(long id, char * title, Owner o,short typeId,long parentId, Date d,Tags t,int score, int comentCount,int answerCount,LPOST lpost);
long get_lid(LPOST p);
char * get_ltitle(Post p);
Owner get_lautor(Post p);
short get_ltypeId(Post p);
long get_lparentId(Post p);
Date get_lCreationDate(Post p);
Tags get_lTags(Post p);
int get_lscore(Post p);
int get_lcomentCount(Post p);
int get_lanswerCount(Post p);
int is_lpergunta(Post p);
LONG_pair perguntasrespostas (LPOST p);
void free_post(Post p)


#endif
