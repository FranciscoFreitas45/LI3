#ifndef __USERS_H__
#define __USERS_H__

#include "posts.h"
#include "user.h"
#include "data.h"

typedef struct users * Users;

void shiftright(Post *t, int ind, int Numposts);
void inserePost(Post p, Users u);
Users createUsers(long id, int reputation, char * name,char *bio,int Numposts,Post *p);
long get_Uid(Users u);
int get_Ureputation(Users u);
char * get_Uname(Users u);
char * get_Ubio(Users u);
int get_numpost(Users u);
Post * get_lista_de_posts(Users u);
Users userclone(Users u);
Post* lista_postsclone(Post* p ,int Numposts);
void freeuser(Users gajo);


#endif
