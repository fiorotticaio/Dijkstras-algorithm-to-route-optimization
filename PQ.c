#include "PQ.h"

struct pq_st {
    Item* pq;
    int* map;
    int N;
};

static void swap(Pq* pQueue, int i, int j) {
    exch(pQueue->pq[i], pQueue->pq[j]);
    pQueue->map[id(pQueue->pq[i])] = i;
    pQueue->map[id(pQueue->pq[j])] = j;
}

void fix_up(Pq* pQueue, Item* a, int k) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(pQueue, k, k/2);
        k = k/2;
    }
}

void fix_down(Pq* pQueue, Item* a, int sz, int k){
    while (2*k <= sz) {
        int j = 2*k;
        if (j < sz && more(a[j], a[j+1])){
            j++;
        }
        if (!more(a[k], a[j])) {
            break;
        }
        swap(pQueue, k, j);
        k = j;
  }
}

Pq* PQ_init(int maxN) {
    Pq* pQueue = malloc(sizeof(Pq));
    pQueue->pq = (Item*) malloc((maxN+1) * sizeof (Item));
    pQueue->map = (int*) malloc((maxN+1) * sizeof (int));
    pQueue->N = 0;
    return pQueue;
}

void PQ_insert(Pq* pQueue, Item v) {
    pQueue->N++;
    pQueue->pq[pQueue->N] = v;
    pQueue->map[id(v)] = pQueue->N;
    fix_up(pQueue, pQueue->pq, pQueue->N);
}

Item PQ_delmin(Pq* pQueue) {
    Item min = pQueue->pq[1];
    swap(pQueue, 1, pQueue->N);
    pQueue->N--;
    fix_down(pQueue, pQueue->pq, pQueue->N, 1);
    return min;
}

Item PQ_min(Pq* pQueue) {
    return pQueue->pq[1];
}

void PQ_decrease_key(Pq* pQueue, int id, double value) {
    int i = pQueue->map[id];
    value(pQueue->pq[i]) = value;
    fix_up(pQueue, pQueue->pq, i);
}

bool PQ_empty(Pq* pQueue) {
    return pQueue->N == 0;
}

int  PQ_size(Pq* pQueue) {
    return pQueue->N;
}

void PQ_finish(Pq* pQueue) {
    free(pQueue->pq);
    free(pQueue->map);
    free(pQueue);
}

void imprimePq(Pq* pQueue) {
    int i = 0;
    for (i = 0; i < pQueue->N; i++) {
        printf("identificador: %d, value: %lf\n", id(pQueue->pq[i+1]), value(pQueue->pq[i+1]));
    }
    printf("\n");
}