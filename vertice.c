#include "vertice.h"

struct vertice {
  int id;
  int* idArestasVizinhas;
  int numVizinhos;
};

Vertice* inicializaVertice(int id) {
  Vertice* v = (Vertice*) malloc(sizeof(Vertice));
  v->id = id;
  v->idArestasVizinhas = NULL; // Inicialmente, não tem vizinhos
  v->numVizinhos = 0;
  return v;
}

void adicionaArestaVizinha(Vertice* v, int idAresta) {
  v->idArestasVizinhas = (int*) realloc(v->idArestasVizinhas, (v->numVizinhos + 1) * sizeof(int));
  v->idArestasVizinhas[v->numVizinhos] = idAresta;
  v->numVizinhos++;
}

void destroiVertice(Vertice* v) { 
  free(v->idArestasVizinhas);
  free(v); 
}

void imprimeVertice(Vertice* v) { 
  printf("Vertice %d\n", v->id); 
  printf("Vizinhos (%d): ", v->numVizinhos);
  int i = 0;
  for (i = 0; i < v->numVizinhos; i++) {
    printf("%d ", v->idArestasVizinhas[i]);
  }
  printf("\n");  
}

int getIdVertice(Vertice* v) { return v->id; }

int getNumVizinhosVertice(Vertice* v) { return v->numVizinhos; }

int* getIdArestasVizinhasVertice(Vertice* v) { return v->idArestasVizinhas; }