
#include "users.h"
#include "glib.h"
#include <stdlib.h>
#include <stdio.h>
#include "structgen.h"
#include "common.h"
#include "data.h"


/**
* @file structgen.c
* @author Grupo56
* @date 5 May 2018
* @brief Guarda a informação necesaria em arrays que envolva sempre duas variaveis(uma int e outra long)
* como por exemplo id de users e o numero de posts deles
*/

struct arraygeral{
	int tamanho;
	int used;
	int *array1;
	long *array2;
};
/**
 * @brief Guarda de uma tag e as vezes que foi utilizada
 */

struct auxTags{
	int count;
	long id;
	char *name;
};
/**
 * @brief Guarda a informação necesaria em arrays que envolva sempre duas variaveis(uma int e outra do tipo DATA)
 * como por exemplo id de users e o numero de posts deles
 */

struct arraygeralDATA{
	int tamanho;
	int used;
	DATA *array1;
	long *array2;
};

/**
 * @brief Guarda a informação necesaria em numa stack
 */

struct Stack{
	int tamanho;
	int used;
	int *s;
};

/**
  *@brief Cria a struct arraygeral
  *@param tamanho da struct
  *@return Apontador para arraygeral
  */

ARRAY creat_ARRAY(int tamanho){
	ARRAY arr= malloc(sizeof(struct arraygeral));
	arr->tamanho=tamanho;
	arr->used=0;
	arr->array1=malloc((tamanho+1) *sizeof(int));
	arr->array2=malloc((tamanho+1) *sizeof(long));
	return arr;
}
/**
  *@brief Cria a struct arraygeralDATA
  *@param tamanho da struct
  *@return Apontador para arraygeralDATA
  */

ARRAYD creat_ARRAYD(int tamanho){
	ARRAYD arr= malloc(sizeof(struct arraygeralDATA));
	arr->tamanho=tamanho;
	arr->used=0;
	arr->array1=malloc((tamanho+1) *sizeof(DATA));
	arr->array2=malloc((tamanho+1) *sizeof(long));
	return arr;
}


/**
  *@brief Devolve o tamanho da struct arraygeral
  *@param  ARRAY
  *@return Tamanho
  */

int get_tamanho(ARRAY arr){
	return arr->tamanho;
}

/**
  *@brief Devolve o tamanho da struct arraygeralDATA
  *@param  ARRAYD
  *@return Tamanho
  */
int get_tamanhoD(ARRAYD arr){
	return arr->tamanho;
}

/**
  *@brief Devolve o valor do que esta a ser usado na struct arraygeral
  *@param  ARRAY
  *@return Used
  */


int get_used (ARRAY arr){
	return arr->used;
}

/**
  *@brief Devolve o valor do que esta a ser usado na struct arraygeralDATA
  *@param  ARRAYD
  *@return Used
  */


int get_usedD(ARRAYD arr){
	return arr->used;
}

/**
  *@brief Devolve o primeiro array da  struct arraygeral
  *@param  ARRAY
  *@return Apontador para a primeira posição do  array
  */


int * get_array(ARRAY arr){
	return arr->array1;
}

/**
  *@brief Devolve o segundo array da  struct arraygeral
  *@param  ARRAY
  *@return Apontador para a primeira posição do  array
  */

long *get_arrayP(ARRAY arr){
	return arr->array2;
}

/**
  *@brief Alterar o tamanho da struct
  *@param  ARRAY
  *@param  tamanho
  */

void set_tamanho(ARRAY arr,int tamanho){
	arr->tamanho=tamanho;
}

/**
  *@brief Aloca mais espaço para a struct
  *@param  ARRAY
  *@param  tamanho
  */


void alloc_long(ARRAY arr,int tamanho){
		arr->array1=(int*)realloc(arr->array1,tamanho *sizeof(int));
		arr->array2=(long*)realloc(arr->array2,tamanho *sizeof(long));
		arr->tamanho=tamanho;
}


/**
  *@brief Devolve o minimo da função
  *@param  array de inteiros
  *@param  N
  *@return minimo
  */

int minimo( int* arr,int N){

		return arr[N-1];
}


/**
  *@brief Insere um valor e um id á struct arraygeral
  *@param  ARRAY
  *@param  valor
  *@param  id
  */

void insere(ARRAY v, int x,long id) {
if(v->used>=v->tamanho){
		return;
	}
else{
v->array1[v->used]=x;
v->array2[v->used]=id;
v->used++;
}

}



/**
  *@brief Insere uma Data e um id á struct arraygeralDATA
  *@param  ARRAY
  *@param  DATA
  *@param  id
  */

void insere_DATA(ARRAYD v, DATA x,long id) {
if(v->used>=v->tamanho){

		return;
	}
else{
v->array1[v->used]=x;
v->array2[v->used]=id;
v->used++;
}
}


/**
  *@brief Verifica se um id esta no array
  *@param  ARRAY
  *@param  numero de indices do array usados
  *@param  id
  *@return 1 ou 0
  */

int verifica_inserido_long(long * arr,int N ,long id){
	int i;
	int flag=0;
		for(i=0;i<N && flag==0;i++)
			if (arr[i]==id)
				flag=1;
return flag;

}

/**
  *@brief Função usada no g_tree_foreach Insere na struct arraygeral o id e os numero de posts de um user
  *@param  key
  *@param  nodo da Gtree de users
  *@param  ARRAY
  *@return False para iterar a Gtree até ao fim
  */



gboolean runUsers(gpointer key,gpointer value,gpointer data){

		ARRAY arr=(ARRAY) data;

		Users u= (Users) value;

		int numpost=get_numpost(u);
		long id =get_Uid(u);
			insere(arr,numpost,id);

return FALSE;

}

/**
  *@brief Verifica se uma DATA esta no array
  *@param  ARRAY
  *@param  numero de indices do array usados
  *@param  data
  *@return 1 ou 0
  */



int verifica_inserido_DATA(DATA* arr,int N ,DATA id){
	int i;
	int flag=1;
		for(i=0;i<N&&flag;i++)
			 if(comparaDatas (arr[i],id)==0)
			 	flag=0;

return flag;

}

/**
  *@brief Swap de um array de longs
  *@param  array de longs
  *@param  indice1
  *@param  indice2
  */

void swapl (long*arr,int max,int first){
			int tmp =arr[max];
			 arr[max]=arr[first];
			 arr[first]=tmp;
}

/**
  *@brief Swap de um array de inteiros
  *@param  array de inteiros
  *@param  indice1
  *@param  indice2
  */

void swapi (int*arr,int max,int first){
			int tmp =arr[max];
			 arr[max]=arr[first];
			 arr[first]=tmp;
}

/**
  *@brief Ordena o arraygeral
  *@param  ARRAY
  *@param  numero de indices do array usados
  *@param  posição do array
  */



void getNMAX(ARRAY v,int N,int first){
	int i;
	int max=0;
	int maior=v->array1[v->used-1];
	if(N==0)
	return;
        for(i=v->used-1;i>first-1;i--){
					if(maior<v->array1[i]){
						maior=v->array1[i];
						max = i;
					}
				}
				if(max!=first){
					swapl(v->array2,max,first);
					swapi(v->array1,max,first);
				}
				getNMAX(v,(N-1),(first+1));
}


/**
  *@brief Insere no na struct arraygeral
  *@param  ARRAY
  *@param  valor a inserir
  *@param  valor a inserir
  */


void inseresimples(ARRAY v,int x,long id){
	if(v->used == v->tamanho ){
	 alloc_long(v, (v->tamanho +1));
	}
   v->array1[v->used]=x;
	 v->array2[v->used]=id;
	 v->used++;
}

/**
  *@brief Incrementa  o numero de vezes que o id é usado.
  *@param  ARRAY
  *@param  id
  */


void incforquery7(ARRAY v, long id){
	int i;
	for(i=0;i<v->used;i++){
		if(v->array2[i]==id){
		v->array1[i]++;
		return;
    }
	}
	return;
}



/**
  *@brief Cria uma struct do tipo arraygeral para tags
  *@param  id
  *@param  nome da tag
  *@return apontador para a struct
  */





AUXTAGS creat_ARRAY_TAGS(long id, char *name){
	AUXTAGS arr= malloc(sizeof(struct auxTags));
	arr->count=1;
	arr->id=id;
	arr->name=name;
	return arr;
}

/**
  *@brief Devolve o id da tag
  *@param  AUXTAGS
  *@return id da tag
  */

long get_AUXTAGS_id(AUXTAGS t){
	return t->id;
}

/**
  *@brief Devolve quantas vezes a tag foi usada
  *@param  AUXTAGS
  *@return quantas vezes a tag foi usada
  */
int get_AUXTAGS_count(AUXTAGS t){
	return t->count;
}


/**
  *@brief Devolve o nome da tag
  *@param  AUXTAGS
  *@return nome da tag
  */

char * get_AUXTAGS_name(AUXTAGS t){
	return mystrdup(t->name);
}

/**
  *@brief incrementa o numero de vezes que a tag foi usada
  *@param  AUXTAGS
  */


void inc_count(AUXTAGS t){
	t->count++;
}


/**
  *@brief Dá free á struct arraygeral
  *@param  ARRAY
  */


void free_arraygeral(ARRAY v){
	free(v->array1);
	free(v->array2);
	free(v);
}

/**
  *@brief Dá free á struct arraygeralDATA
  *@param  ARRAYD
  */


void free_arraygeralDATA(ARRAYD v){
	int i;
	for(i=0;i<v->used;i++){
		free_data(v->array1[i]);
	}
	free(v->array1);
	free(v->array2);

	free(v);
}


/**
  *@brief Cria uma stack
  *@param  capacidade da stack
  */



struct Stack* createStack(int capacity)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->tamanho = capacity;
    stack->used = 0;
    stack->s = (int*) malloc(stack->tamanho * sizeof(int));
    return stack;
}

/**
  *@brief Verifica se a stack ta cheia
  *@param  Stack
  *@return 0 ou 1
  */

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{   return stack->used == stack->tamanho; }


/**
  *@brief Verifica se a stack ta vazia
  *@param  Stack
  *@return 0 ou 1
  */
// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{   return stack->used == 0;  }

/**
  *@brief Coloca na stack
  *@param  Stack
  *@param  valor a colocar na stack
  */



// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->s[stack->used++] = item;
}

/**
  *@brief Retira da stack
  *@param  Stack
  *@return valor da stack
  */

// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->s[stack->used--];
}

/**
  *@brief verifica se um valor está na stack
  *@param  Stack
  *@param  valor a procurar na stack
  *@return 0 ou 1
  */


int contido(struct Stack* stack,int x){
	int i;
 	int flag=0;
	for(i=0;i<stack->used && !flag;i++){
			if(stack->s[i]==x)
				flag=1;
	}
	return flag;
}

/**
  *@brief Liberta a memoria alocada  na stack
  *@param  Stack
  */


void free_stack(struct Stack*stack){
	free(stack->s);
	free(stack);
}

/**
  *@brief Coloca no LONG_list N perguntas em que participaram dois users
  *@param  Struct arraygeralDATA do user1
  *@param  Struct arraygeralDATA do user2
  *@param  N passado como argumento á struct both participated
  *@param  LONG_list
  */

void getNComuns(ARRAYD array1, ARRAYD array2, int N, LONG_list list){

	int used1 = array1->used;
	int used2 = array2->used;
	int ks;

	long * arr1 = malloc(used1 *sizeof(long));
	for(ks = 0; ks < used1; ks++)
		arr1[ks] = array1->array2[ks];
	long * arr2 = malloc(used2 *sizeof(long));
	for(ks = 0; ks < used2; ks++)
		arr2[ks] = array2->array2[ks];

		struct Stack* stack=createStack(used1);
	int i=0,conta=0;
	  while(i < used1 && conta<N ){
						long xx=arr1[i];
							if(verifica_inserido_long(arr2,ks,xx))
								if(!contido(stack,arr1[i])){
									push(stack,arr1[i]);
						 set_list(list, i, arr1[i]);
						 conta ++;
					 }

 					i++;
		 }
		if(conta < N){
			for(; conta < N; conta++){
				set_list(list, conta, -1);
				conta ++;
			}
		}
		free(arr1);
		free(arr2);
		free_stack(stack);
}


/**
  *@brief Ordena a dois arrays
  *@param array de int
  *@param array de long
  *@param indice do array
  *@param indice do array
  *@param indice do array
  */



void merge(int arri[] ,long arrl [], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int arrayI1[n1] , arrayI2[n2];
    long arrayL1[n1],arrayL2[n2];
		for (i = 0; i < n1; i++)
			arrayI1[i] = 0;

		for (i = 0; i < n1; i++)
			arrayI2[i] = 0;

		for (i = 0; i < n1; i++)
			arrayL1[i] = 0;

		for (i = 0; i < n1; i++)
			arrayL2[i] = 0;

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        arrayI1[i] = arri[l + i];
        arrayL1[i]= arrl[l+i];
      }
    for (j = 0; j < n2; j++){
        arrayI2[j] = arri[m + 1+ j];
        arrayL2[j] = arrl[m+1+j];
      }
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (/*arrayI2[i] && arrayI1[j] && */arrayI1[i] > arrayI2[j])
        {
            arri[k] = arrayI1[i];
            arrl[k]=arrayL1[i];
            i++;
        }
        else
        {
            arri[k] = arrayI2[j];
            arrl[k]=arrayL2[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arri[k] = arrayI1[i];
        arrl[k]=arrayL1[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arri[k] = arrayI2[j];
        arrl[k]=arrayL2[j];
        j++;
        k++;
    }
}


/**
  *@brief Ordena a struct arraygeral
  *@param indice do array
  *@param indice do array
  */





/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(ARRAY arr,int l, int r)
{
	if(arr){
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr,l, m);
        mergeSort(arr,m+1, r);

        merge(arr->array1,arr->array2, l, m, r);
    }
	}
}


/**
  *@brief Ordena a dois arrays
  *@param array de int
  *@param array de DATA
  *@param indice do array
  *@param indice do array
  *@param indice do array
  */

void mergeData(DATA arrD[] ,long arrl [], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    DATA arrayD1[n1] , arrayD2[n2];
    long arrayL1[n1],arrayL2[n2];
		for (i = 0; i < n1; i++)
			arrayD1[i] = NULL;

		for (i = 0; i < n1; i++)
			arrayD2[i] = NULL;

		for (i = 0; i < n1; i++)
			arrayL1[i] = 0;

		for (i = 0; i < n1; i++)
			arrayL2[i] = 0;

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        arrayD1[i] = arrD[l + i];
        arrayL1[i]= arrl[l+i];
      }
    for (j = 0; j < n2; j++){
        arrayD2[j] = arrD[m + 1+ j];
        arrayL2[j] = arrl[m+1+j];
      }
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (comparaDatas(arrayD1[i],arrayD2[j])==1)
        {
            arrD[k] = arrayD1[i];
            arrl[k]=arrayL1[i];
            i++;
        }
        else
        {
            arrD[k] = arrayD2[j];
            arrl[k]=arrayL2[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arrD[k] = arrayD1[i];
        arrl[k]=arrayL1[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arrD[k] = arrayD2[j];
        arrl[k]=arrayL2[j];
        j++;
        k++;
    }
}
/**
  *@brief Ordena a struct arraygeralDATA
  *@param indice do array
  *@param indice do array
  */





/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSortDATA(ARRAYD arr,int l, int r)
{
	if(arr){
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSortDATA(arr,l, m);
        mergeSortDATA(arr,m+1, r);

        mergeData(arr->array1,arr->array2, l, m, r);
    }
	}
}

/**
  *@brief Concatena o caminho dos ficheiros com os ficheiros
  *@param caminho
  *@param ficheiro
  *@return caminho para o ficheiro
  */




char* concat(const char *path, const char *ficheiro){
    char *caminho_to_ficheiro = malloc(strlen(path)+strlen(ficheiro)+1);
    strcpy(caminho_to_ficheiro, path);
    strcat(caminho_to_ficheiro, ficheiro);
    return caminho_to_ficheiro;
}


/**
  *@brief Dá free á struct auxTags
  *@param AUXTAGS
  */



void free_AUXTAG(AUXTAGS t){
	free(t);
}
