#include "vertice.h"

struct vertice {
  int id;
  Vertice** vizinhos;
  int numVizinhos;
};

Vertice* inicializaVertice(int id) {
  Vertice* v = (Vertice*) malloc(sizeof(Vertice));
  v->id = id;
  v->vizinhos = NULL; // Inicialmente, não tem vizinhos
  v->numVizinhos = 0;
  return v;
}

void adicionaVerticeVizinho(Vertice* v, Vertice* vizinho) {
  v->numVizinhos++;
  v->vizinhos = (Vertice**) realloc(v->vizinhos, v->numVizinhos * sizeof(Vertice*));
  v->vizinhos[v->numVizinhos - 1] = vizinho;
}

void destroiVertice(Vertice* v) { 
  free(v->vizinhos);
  free(v); 
}

void imprimeVertice(Vertice* v) { 
  printf("Vertice %d, ", v->id); 
  printf("Vizinhos: ");
  int i = 0;
  for (i = 0; i < v->numVizinhos; i++) {
    printf("%d ", getIdVertice(v->vizinhos[i]));
  }
  printf("\n");  
}

int getIdVertice(Vertice* v) { return v->id; }