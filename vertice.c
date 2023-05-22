#include "vertice.h"

struct vertice {
  int id;
  // Talvez colocar alguma coisa relacionada ao tempo aqui
};

Vertice* inicializaVertice(int id) {
  Vertice* v = (Vertice*) malloc(sizeof(Vertice));
  v->id = id;
  return v;
}

void destroiVertice(Vertice* v) { free(v); }

void imprimeVertice(Vertice* v) { printf("Vertice %d\n", v->id); }

int getIdVertice(Vertice* v) { return v->id; }