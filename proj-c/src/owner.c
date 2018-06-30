#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "owner.h"
#include "common.h"

/**
* @file owner.c
* @author Grupo56
* @date 5 May 2018
* @brief A partir da struct Posts, guarda mos uma string com o nome do autor, o
* id dele e a reputacao
*/
struct owner {
	char* name;
	long id;
	int reputation;
};

/**
* @brief Cria um Owner, atualizando o nome, id e a reputacao do mesmo
* @param name
* @param id
* @param reputation
* @return Retorna um Owner
*/
Owner createOwner(char *name, long id, int reputation) {
    Owner o = malloc(sizeof(struct owner));
    o->name = name;
    o->id = id;
    o->reputation = reputation;
    return o;
}

/**
* @brief Procura o nome de um owner, a partir de um Owner
* @param o Owner
* @return Retorna o nome do Owner
*/
char * get_Oname(Owner o) {
    return mystrdup (o->name);
}

/**
* @brief Procura a partir de um Owner, o seu id
* @param o Owner
* @return Retorna o id do Owner
*/
long get_Oid(Owner o) {
    return o->id;
}

/**
* @brief A partir de um Owner, procura o valor da sua reputacao
* @param o Owner
* @return Retorna a reputacao do Owner
*/
int get_Oreputation(Owner o) {
    return o->reputation;
}

/**
* @brief Funcao que liberta a memoria alocada para o nome do Owner e o id do Owner 
* @param o Owner
*/
void free_owner(Owner o) {
    free(o->name);
    free(o);
}
