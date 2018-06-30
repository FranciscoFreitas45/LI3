#ifndef __TAG_H__
#define __TAG_H__


typedef struct tag_ligadas * Tags;



int commontag_compare (char * t1, Tags t2);
Tags add_tag (char* string ,Tags lista);
Tags stringToTag_ligada(char* str , Tags t);
void printftag(Tags t);
void free_tag(Tags t);
Tags proximo(Tags t);
char* get_tag_ligada(Tags t);
Tags clone_Tags(Tags l);


#endif