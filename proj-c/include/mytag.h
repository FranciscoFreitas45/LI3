#ifndef __MYTAG_H__
#define __MYTAG_H__


typedef struct mytags *TAGS;

TAGS create_tag(long id, char *name);
long get_tag_id(TAGS t);
char * get_tag_name(TAGS t );
void set_id(TAGS t,long id);
void free_TAG(TAGS t);




#endif
