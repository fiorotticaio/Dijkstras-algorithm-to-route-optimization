#include "aresta.h"

Aresta *inicializaAresta(Vertice *vOrigem, Vertice *vDestino, double dist, double peso) {
  Aresta* a = (Aresta*) malloc(sizeof(Aresta));
  a->vOrigem = vOrigem;
  a->vDestino = vDestino;
  a->dist = dist;
  a->peso = peso;
  return a;
}

void destroiAresta(Aresta* a) { 
  // destroiVertice(a->vOrigem);
  // destroiVertice(a->vDestino);
  free(a); 
}

void imprimeAresta(Aresta* a) { 
  printf("Aresta %d -> %d, dist: %.5lf, peso: %.5lf\n", a->vOrigem, a->vDestino, a->dist, a->peso ''); 
}

Vertice* getVerticeOrigemAresta(Aresta* a) { return a->vOrigem; }

Vertice* getVerticeDestinoAresta(Aresta* a) { return a->vDestino; }

double getDistAresta(Aresta* a) { return a->dist; }

double getPesoAresta(Aresta* a) { return a->peso; }

void setPesoAresta(Aresta* a, double peso) { a->peso = peso; }