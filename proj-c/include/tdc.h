#ifndef __TDC_H__
#define __TDC_H__


#include "load.h"
#include "posts.h"
#include "users.h"
#include "date.h"
#include "pair.h"
#include "list.h"
#include "user.h"
#include "structgen.h"
#include "data.h"


typedef struct TDC_community *TAD_community;
TAD_community creat_TAD();
TAD_community load(TAD_community com, char* dump_path);
void printintrevalotdc(TAD_community com, DATA begin,DATA end);
STR_pair info_from_post(TAD_community com, long id);
USER get_user_info(TAD_community com, long id);
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end);
LONG_list most_answered_questions(TAD_community com,int N, Date begin, Date end);
LONG_list contains_word(TAD_community com,char *word,int N);
LONG_list most_voted_answers(TAD_community com,int N, Date begin, Date end);
LONG_pair total_posts(TAD_community com, Date begin, Date end);
LONG_list top_most_active(TAD_community com, int N);
long better_answer(TAD_community com, long id);
//LONG_list both_participated(TAD_community com, long id1, long id2, int N);
void free_TCD(TAD_community com);
#endif
