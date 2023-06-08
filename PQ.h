#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "vertice.h"

typedef struct pq Pq;

Pq* PQ_init(int maxN); // cria uma min PQ com capacidade maxN
void PQ_insert(Pq* p,Vertice* new);   // Insere Vertice na PQ. A maior prioridade é a do Vertice com menor campo 'value'
Vertice* PQ_delmin(Pq* p);       // Remove Vertice com menor campo 'value' da PQ
void PQ_decrease_key(Pq* p, int id, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Vertice* PQ_min(Pq* p);          // Retorna Vertice com menor campo 'value' da PQ
bool PQ_empty(Pq* p);        // Retorna True se a PQ não tem elementos
int  PQ_size(Pq* p);         // Número de elementos na PQ
void PQ_finish(Pq* p);       // Libera memória

#endif
