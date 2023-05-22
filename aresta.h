#ifndef ARESTA_H
#define ARESTA_H

#include <stdio.h>
#include <stdlib.h>
#include "vertice.h"

typedef struct aresta Aresta;

/// @brief Calcula o peso de uma aresta
/// @param dist
/// @param velMedia
/// @return Peso da aresta
double calculaPesoAresta(double dist, double velMedia);

/// @brief Inicializa uma aresta
/// @param vOrigem 
/// @param vDestino 
/// @param dist 
/// @param velMedia 
/// @return Ponteiro para a aresta inicializada
Aresta* inicializaAresta(Vertice* vOrigem, Vertice* vDestino, double dist, double velMedia);

/// @brief Libera a memoria alocada para uma aresta
/// @param a 
void destroiAresta(Aresta* a);

/// @brief Imprime uma aresta
/// @param a 
void imprimeAresta(Aresta* a);

/// @brief Retorna o vertice de origem de uma aresta
/// @param a 
/// @return Vértice de origem
Vertice* getVerticeOrigemAresta(Aresta* a);

/// @brief Retorna o vertice de destino de uma aresta
/// @param a 
/// @return Vértice de destino
Vertice* getVerticeDestinoAresta(Aresta* a);

/// @brief Retorna a distância de uma aresta
/// @param a 
/// @return Distância da aresta
double getDistAresta(Aresta* a);

/// @brief Retorna a velocidade média de uma aresta
/// @param a 
/// @return Velocidade média da aresta
double getVelMediaAresta(Aresta* a);

/// @brief Retorna o peso de uma aresta
/// @param a 
/// @return Peso da aresta
double getPesoAresta(Aresta* a);

/// @brief Define a velocidade média de uma aresta
/// @param a 
/// @param velMedia 
void setVelMediaAresta(Aresta* a, double velMedia);

/// @brief Define o peso de uma aresta
/// @param a 
/// @param peso 
void setPesoAresta(Aresta* a, double peso);

#endif // ARESTA_H