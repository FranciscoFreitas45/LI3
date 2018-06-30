#ifndef __OWNER_H__
#define __OWNER_H__

typedef struct owner* Owner;
Owner createOwner(char *name, long id, int reputation);
char * get_Oname(Owner o);
long get_Oid(Owner o);
int get_Oreputation(Owner o);
void free_owner(Owner o);
#endif
