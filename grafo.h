#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include "vertice.h"
#include "aresta.h"

typedef struct grafo Grafo;

/// @brief Lê um grafo do arquivo de entrada
/// @param caminhoArquivoEntrada 
/// @return Grafo gerado a partir do arquivo de entrada
Grafo* leGrafo(char* caminhoArquivoEntrada);

/// @brief Inicializa um grafo
/// @param v 
/// @param a 
/// @param nVertices 
/// @param nArestas 
/// @return Ponteiro para o grafo inicializado
Grafo* inicializaGrafo(Vertice** v, Aresta** a, int numVertices, int numArestas, int idVerticeOrigem, int idVerticeDestino);

/// @brief Libera a memoria alocada para um grafo
/// @param g 
void destroiGrafo(Grafo* g);

/// @brief Imprime um grafo
/// @param g 
void imprimeGrafo(Grafo* g);

/// @brief Retorna os vértices de um grafo
/// @param g 
/// @return Vértices do grafo
Vertice** getVerticesGrafo(Grafo* g);

/// @brief Retorna as arestas de um grafo
/// @param g 
/// @return Arestas do grafo
Aresta** getArestasGrafo(Grafo* g);

/// @brief Retorna o número de arestas de um grafo
/// @param g 
/// @return Número de arestas do grafo
int getNumVerticesGrafo(Grafo* g);

/// @brief Retorna o número de arestas de um grafo
/// @param g 
/// @return Número de arestas do grafo
int getNumArestasGrafo(Grafo* g);

/// @brief Define o número de vértices de um grafo
/// @param g 
/// @param numVertices 
void setNumVerticesGrafo(Grafo* g, int numVertices);

/// @brief Define o número de arestas de um grafo
/// @param g 
/// @param numArestas 
void setNumArestasGrafo(Grafo* g, int numArestas);

#endif // !GRAFO_H