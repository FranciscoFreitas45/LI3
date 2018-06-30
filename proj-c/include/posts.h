#ifndef __POSTS_H__
#define __POSTS_H__

#include "owner.h"
#include "data.h"
#include "tag_ligada.h"
#include "data.h"


typedef struct post * Post;

Post createPost(long id, char * title,long ownerId, Owner o,short typeId,long parentId, DATA d,Tags t,int score, int comentCount,int answerCount);
long get_id(Post p);
char * get_title(Post p);
long get_ownerId(Post p);
short get_typeId(Post p);
long get_parentId(Post p);
DATA get_CreationDate(Post p);
Tags get_Tags(Post p);
int get_score(Post p);
int get_comentCount(Post p);
int get_answerCount(Post p);
void print_tag(Post p);
char* get_NAME_OwnerPost(Post p);
long get_ID_ownerPost(Post p);
int get_REPUTACION_ownerPost(Post p);
int get_DATE_DAY_post(Post p);
int get_DATE_MONTH_post(Post p);
int get_DATE_YEAR_post(Post p);
int get_DATE_HORA_post(Post p);
int get_DATE_MINUTO_post(Post p);
int get_DATE_SEGUNDO_post(Post p);
void set_Owner(Post p,Owner o );
long getquestionID(Post p);
void free_post(Post p);

#endif
