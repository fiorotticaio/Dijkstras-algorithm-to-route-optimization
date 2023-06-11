#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "vertice.h"
#include "item.h"

typedef struct pq_st Pq;

/// @brief Cria uma min PQ com capacidade maxN
/// @param maxN 
/// @return Ponteiro para PQ alocada
Pq* PQ_init(int maxN);

/// @brief Insere Vertice na PQ. A maior prioridade é a do Vertice com menor campo 'value'
/// @param p 
/// @param item 
void PQ_insert(Pq* p, Item item);

/// @brief Remove Vertice com menor campo 'value' da PQ
/// @param p 
/// @return Vertice com menor campo 'value' da PQ, agora fora da PQ
Item PQ_delmin(Pq* p);

/// @brief Muda a prioridade do nó com identificador 'id' para 'value'
/// @param p 
/// @param id 
/// @param value 
void PQ_decrease_key(Pq* p, int id, double value);

/// @brief Retorna Vertice com menor campo 'value' da PQ
/// @param p 
/// @return Vertice com o menor campo 'value' da PQ
Item PQ_min(Pq* p);

/// @brief Retorna True se a PQ não tem elementos
/// @param p 
/// @return Valor booleano com o resultado da verificação
bool PQ_empty(Pq* p);

/// @brief Retorna o número de elementos na PQ
/// @param p 
/// @return  Número de elementos na PQ
int  PQ_size(Pq* p);

/// @brief Libera memória de PQ
/// @param p 
void PQ_finish(Pq* p);

/// @brief Utilizado para Debugin, imprime a PQ
/// @param pQueue 
void imprimePq(Pq* pQueue); 

#endif // PQ_H