#ifndef __DATA_H__
#define __DATA_H__
#include "pair.h"
#include "date.h"

typedef struct data * DATA;

DATA create_data_dia(char* data);
DATA insereData (char *data);
DATA dateTodata(Date a);
int comparaDatas (DATA d1, DATA d2);
int get_data_dia(DATA d);
int get_data_mes(DATA d);
int get_data_ano(DATA d);
int get_data_hora(DATA d);
int get_data_minuto(DATA d);
int get_data_segundo(DATA d);
DATA clone_DATA(DATA d);
void free_data(DATA d);

#endif
