#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "vertice.h"
#include "item.h"

typedef struct pq_st Pq;

Pq* PQ_init(int maxN); // cria uma min PQ com capacidade maxN
void PQ_insert(Pq* p, Item item);   // Insere Vertice na PQ. A maior prioridade é a do Vertice com menor campo 'value'
Item PQ_delmin(Pq* p);       // Remove Vertice com menor campo 'value' da PQ
void PQ_decrease_key(Pq* p, int id, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Item PQ_min(Pq* p);          // Retorna Vertice com menor campo 'value' da PQ
bool PQ_empty(Pq* p);        // Retorna True se a PQ não tem elementos
int  PQ_size(Pq* p);         // Número de elementos na PQ
void PQ_finish(Pq* p);       // Libera memória
void imprimePq(Pq* pQueue);

#endif // PQ_H