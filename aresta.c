#include "aresta.h"

struct aresta {
  int id;
  Vertice* vOrigem;
  Vertice* vDestino;
  double dist;
  double velMedia; // km/h
  double peso;
};

double calculaPesoAresta(double dist, double velMedia) {
  /* Peso da aresta (rodovia): tempo para se deslocar nela */
  return (double) (dist / (velMedia/3.6)); 
}

Aresta *inicializaAresta(int id, Vertice *vOrigem, Vertice *vDestino, double dist, double velMedia) {
  Aresta* a = (Aresta*) malloc(sizeof(Aresta));
  a->id = id;
  a->vOrigem = vOrigem;
  a->vDestino = vDestino;
  a->dist = dist;
  a->velMedia = velMedia;
  a->peso = calculaPesoAresta(dist, velMedia);
  return a;
}

void destroiAresta(Aresta* a) { free(a); }

void imprimeAresta(Aresta* a) { 
  printf("Aresta %d: %d -> %d, dist: %.5lf, velMedia: %.5lf, peso: %.5lf\n", 
    a->id,
    getIdVertice(a->vOrigem), 
    getIdVertice(a->vDestino),
    a->dist,
    a->velMedia,
    a->peso
  ); 
}

Vertice* getVerticeOrigemAresta(Aresta* a) { return a->vOrigem; }

Vertice* getVerticeDestinoAresta(Aresta* a) { return a->vDestino; }

int getIdAresta(Aresta* a) { return a->id; }

double getDistAresta(Aresta* a) { return a->dist; }

double getVelMediaAresta(Aresta* a) { return a->velMedia; }

double getPesoAresta(Aresta* a) { return a->peso; }

void setVelMediaAresta(Aresta* a, double velMedia) { 
  a->velMedia = velMedia;
  a->peso = calculaPesoAresta(a->dist, velMedia); // Atualiza o peso com o novo valor de velocidade
}

void setPesoAresta(Aresta* a, double peso) { a->peso = peso; }

static int comparaArestas(const void* a, const void* b) {
  /* Função de comparação para o qsort */
  Aresta* arestaA = *(Aresta**) a;
  Aresta* arestaB = *(Aresta**) b;
  if (getIdVertice(arestaA->vOrigem) == getIdVertice(arestaB->vOrigem)) 
    return (getIdVertice(arestaA->vDestino) - getIdVertice(arestaB->vDestino));
  else 
    return (getIdVertice(arestaA->vOrigem) - getIdVertice(arestaB->vOrigem)); 
}

void ordenaArestas(Aresta** arestas, int numArestas) {
  /* Utiliza o qsort para ordenar as arestas pelo id do vértice de origem */
  qsort(arestas, numArestas, sizeof(Aresta*), comparaArestas);
}