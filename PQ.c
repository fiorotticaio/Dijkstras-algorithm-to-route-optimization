// TODO: Ajustar para o nosso caso

#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

struct pq{
    Vertice **itens;
    int *map;
    int N;
    int MaxN;
};

static void swap(Pq* p, int i, int j) {
    Vertice* temp;
    temp = p->itens[i];
    p->itens[i] = p->itens[j];
    p->itens[j] = temp;
    p->map[getIdVertice(p->itens[i])] = i;
    p->map[getIdVertice(p->itens[j])] = j;
}

void fix_up(Pq *p, int k) {
    Vertice ** a = p->map;
    while (k > 1 && more(a[k/2], a[k])) {
        swap(p, k, k/2);
        k = k/2;
    }
}

void fix_down(Pq *p, int sz, int k){
    Vertice ** a = p->map;
    while (2*k <= sz) {
        int j = 2*k;
        if (j < sz && more(a[j], a[j+1])){
            j++;
        }
        if (!more(a[k], a[j])) {
            break;
        }
        swap(p, k, j);
        k = j;
  }
}

Pq* PQ_init(int maxN) {
    Pq* novo = malloc(sizeof(Pq));
    novo->itens = (Vertice **) malloc((maxN+1) * sizeof (Vertice*));
    novo->map = (int *) malloc((maxN+1) * sizeof (int));
    novo->N = 0;
    novo->MaxN = maxN;

    return novo;
}

void PQ_insert(Pq* p,Vertice* new) {
    if(p->N==p->MaxN){
        return;
    }
    p->N++;
    p->itens[p->N] = new;
    p->map[getIdVertice(new)] = p->N;
    fix_up(p, p->N); //FIX
}

Vertice* PQ_delmin(Pq* p) {
    Vertice* min = p->itens[1];
    swap(p, 1, p->N);
    p->N--;
    fix_down(p, p->N, 1);
    return min;
}

Vertice* PQ_min(Pq* p) {
    return p->itens[1];
}

void PQ_decrease_key(Pq* p, int id, double value) {
    int i = p->map[id];
    p->map[i] = value;
    fix_up(p, i);
}

bool PQ_empty(Pq* p) {
    return p->N == 0;
}

int  PQ_size(Pq* p) {
    return p->N;
}

void PQ_finish(Pq* p) {
    for(int i = p->N;i<0;i--){
        free(p->itens[i]);
    }
    free(p->map);
    free(p);
}


