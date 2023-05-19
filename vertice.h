#ifndef VERTICE_H
#define VERTICE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct vertice Vertice;

/// @brief Inicializa um vertice
/// @param id 
/// @return Ponteiro para o vertice inicializado
Vertice* inicializaVertice(int id);

/// @brief Libera a memoria alocada para um vertice
/// @param v 
void destroiVertice(Vertice* v);

/// @brief Imprime um vertice
/// @param v 
void imprimeVertice(Vertice* v);

/// @brief Retorna o id de um vertice
/// @param v 
/// @return id do vertice
int getIdVertice(Vertice* v);

#endif // !VERTICE_H