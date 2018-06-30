/*#include <date.h>
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

*/
#include<stdio.h>
#include "interface.h"
#include <time.h>






int main(){
  //Date d = createDate(1,2,2017);
  //printf("Dia: %i\n", get_day(d));
	char *path;
	clock_t t;

	path ="/home/flash_12/Desktop/";

TAD_community com=init();


double a;

t=clock();
	com=load(com,path);
		t = clock()-t;
		a=((double)t)/CLOCKS_PER_SEC;
	printf("load %f\n",a );
	t=clock();
	info_from_post(com,801049);
		t = clock()-t;
		 a=(double) t/(CLOCKS_PER_SEC);
	printf("query 1 %f\n",a );

t = clock();

get_user_info(com, 15811);
t = clock()-t;
a=(double) t/(CLOCKS_PER_SEC);

printf("query 5 %f\n",a);

t = clock();
//LONG_list ll=top_most_active(com, 100000);
LONG_list lll=top_most_active(com,100);
t = clock()-t;
a=(double) t/(CLOCKS_PER_SEC);
printf("query 2 %f\n",a);
//DATA datebegin = insereData("2010-09-13T19:21:30.790");
//DATA dateend = insereData("2016-11-27T07:17:08.433");

//printintrevalotdc(com,datebegin,dateend);
//t = clock();
//both_participated(com,16575,1465 , 13);

char* tag = "package-management";

Date begin =createDate(01,11,2015);
Date end =createDate(30,11,2015);

t=clock();
LONG_pair batata = total_posts(com,begin,end);
t=clock()-t;
a=(double) t/(CLOCKS_PER_SEC);
printf("query 3 %f\n",a);

t=clock();
LONG_list weed = most_answered_questions( com, 10, begin, end);
t=clock()-t;
a=(double) t/(CLOCKS_PER_SEC);
printf("query 7 %f\n",a);

t=clock();
LONG_list dfghjfdfghnbvf= questions_with_tag(com,tag,begin,end);
t=clock()-t;
a=(double) t/(CLOCKS_PER_SEC);
printf("query 4 %f\n",a);

t=clock();
LONG_list qwertyhgfdsa= most_voted_answers(com,5,begin,end);
t=clock()-t;
a=(double) t/(CLOCKS_PER_SEC);
printf("query 6 %f\n",a);

t=clock();
long aaa =better_answer( com,30334);
t=clock()-t;
a=(double) t/(CLOCKS_PER_SEC);
printf("query 10 %f\n",a);

t=clock();
LONG_list welelel= contains_word(com,"kde",10);
t=clock()-t;
a=(double) t/(CLOCKS_PER_SEC);
printf("query 8 %f\n",a);

t=clock();
LONG_list aaaa= most_used_best_rep(com, 5, begin,end);
t=clock()-t;
a=(double) t/(CLOCKS_PER_SEC);
printf("query 11 %f\n",a);

t=clock();
LONG_list caca = both_participated(com,87,5691,10);
t=clock()-t;
a=(double) t/(CLOCKS_PER_SEC);
printf("query 9 %f\n",a);
free_date(begin);

free_date(end);

//printf("query 3 %f\n",a);
//

com=clean(com);
	return 0;



}
