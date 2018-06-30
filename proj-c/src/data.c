#include <stdlib.h>
#include "data.h"
#include "date.h"

/**
* @file data.c
* @author Grupo56
* @date 5 May 2018
* @brief Guarda a data de um post
*/

struct data{
  int dia;
  int mes;
  int ano;
};

/**
*@brief Converte o tipo de dados Date para DATA
*@param Date
*@return  Data no tipo DATA
*/
DATA dateTodata(Date a){
  DATA data =malloc(sizeof(struct data));
  data->dia=get_day(a);
  data->mes=get_month(a);
  data->ano=get_year(a);
  return data;
}

/**
*@brief Converte a data que está em string para o tipo DATA
*@param char *
*@return  Data no tipo DATA
*/

DATA insereData (char data[]){
  int i = 0;
  char a[5];
  char m[3];
  char d[3];
  for(i=0; data[i] != '-'; i++){
    a[i] = data[i];
  }
  a[i]='\0';
  int year = atoi(a);
  i++;
  int b=0;
  while(data[i] != '-'){
    m[b] = data[i];
    i++;
    b++;
  }
  m[b]='\0';
  int month = atoi(m);
  i++;
  b=0;
  while(data[i] != 'T'){
    d[b] = data[i];
    i++;
    b++;
  }
  d[b] = '\0';
  int day = atoi(d);




  DATA datas = malloc(sizeof (struct data));
  datas->dia = day;
  datas->mes = month;
  datas->ano = year;

  return datas;
}


/**
*@brief Faz um clone da data
*@param DATA
*@return  DATA
*/


DATA clone_DATA(DATA d){
  DATA t = malloc(sizeof(struct data));
  t->dia=d->dia;
  t->mes=d->mes;
  t->ano=d->ano;
  return t;
}


/**
*@brief Compara duas datas.
*@param DATA 
*@param DATA 
*@return Um inteiro que identifica a data maior 
*/


int comparaDatas (DATA d1, DATA d2){
  if (d1->ano < d2->ano) return 2;
    else if (d1->ano > d2->ano) return 1;
  if (d1->mes < d2->mes) return 2;
    else if (d1->mes > d2->mes) return 1;
  if(d1->dia < d2->dia) return 2;
    else if (d1->dia > d2->dia) return 1;
  else return 0;
}


/**
*@brief Devolve o dia da data
*@param DATA 
*@return  dia 
*/

int  get_data_dia(DATA d){
  return d->dia;
}


/**
*@brief Devolve o mes da data
*@param DATA  
*@return  mes 
*/
int get_data_mes(DATA d){
  return d->mes;
}


/**
*@brief Devolve o ano da data
*@param DATA 
*@return  ano
*/
int get_data_ano(DATA d){
  return d->ano;
}


/**
*@brief Liberta a memoria alocado pela a struct DATA
*@param DATA 
*/

void free_data(DATA d){
  free(d);
}
