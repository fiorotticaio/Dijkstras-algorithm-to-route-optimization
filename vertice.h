#ifndef VERTICE_H
#define VERTICE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct vertice Vertice;

/// @brief Inicializa um vertice
/// @param id 
/// @return Ponteiro para o vertice inicializado
Vertice* inicializaVertice(int id);

void adicionaArestaVizinha(Vertice* v, int id);

/// @brief Libera a memoria alocada para um vertice
/// @param v 
void destroiVertice(Vertice* v);

/// @brief Utilizado para Debuging, Imprime um vertice
/// @param v 
void imprimeVertice(Vertice* v);

/// @brief Retorna o id de um vertice
/// @param v 
/// @return id do vertice
int getIdVertice(Vertice* v);

/// @brief Retorna o numero de vizinhos de um vértice
/// @param v 
/// @return numero de vizinhos de um vértice
int getNumVizinhosVertice(Vertice* v);

/// @brief Retorna o vetor de IDs de arestas vizinhas de um vértice
/// @param v 
/// @return IDs de arestas vizinhas de um vertice 
int* getIdArestasVizinhasVertice(Vertice* v);

#endif // VERTICE_H