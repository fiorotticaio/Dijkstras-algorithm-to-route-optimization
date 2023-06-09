#include "grafo.h"

struct grafo {
  Vertice** vertices;
  Aresta** arestas;
  int numVertices;
  int numArestas;
  int idVerticeOrigem;
  int idVerticeDestino;
  double tempoPercorrido;
  double distanciaPercorrida;
  int* idVerticesPercorridos;
  int numVerticesPercorridos;
};

/* Função auxiliar da leitura do grafa, que verifica se um vértice já foi lido */
static int verticeJaExiste(Vertice** v, int idVertice) {
  if (v[idVertice-1] == NULL) return 0; // -1 porque os id's dos vértices vão de 1 a N, e não de 0 a N-1
  return 1;
  /*
    Podemos fazer isso pois todos os ponteiros
    são inicializados com NULL pelo calloc 
  */
}

Grafo* leGrafo(FILE* arquivoEntrada) {
  int numVertices = 0, numArestas = 0, idVerticeOrigem = 0, idVerticeDestino = 0;
  fscanf(arquivoEntrada, "%d;%d", &numVertices, &numArestas);
  fscanf(arquivoEntrada, "%d;%d", &idVerticeOrigem, &idVerticeDestino);

  double velMedia = 0.0; // Velocidade média inicial de todas as rodovias (arestas)
  fscanf(arquivoEntrada, "%lf", &velMedia);

  /* Criando o vetor de vértices */
  Vertice** vertices = (Vertice**) calloc(numVertices, sizeof(Vertice*));

  /* Criando o vetor de arestas */
  Aresta** arestas = (Aresta**) calloc(numArestas, sizeof(Aresta*));

  int i = 0;
  for (i = 0; i < numArestas; i++) {
    int idVerticeOrigemAresta = 0, idVerticeDestinoAresta = 0;
    double dist = 0.0;
    fscanf(arquivoEntrada, "%d;%d;%lf", &idVerticeOrigemAresta, &idVerticeDestinoAresta, &dist);

    Vertice* vOrigem = NULL;
    Vertice* vDestino = NULL;

    if (!verticeJaExiste(vertices, idVerticeOrigemAresta)) {
      vOrigem = inicializaVertice(idVerticeOrigemAresta); // Criando novo vértice
      vertices[idVerticeOrigemAresta-1] = vOrigem; // Adicionando o vértice no vetor de vértices
      /* -1 porque os id's dos vértices vão de 1 a N, e não de 0 a N-1 */
    } else {
      vOrigem = vertices[idVerticeOrigemAresta-1]; // Pegando o vértice já existente
    } 

    if (!verticeJaExiste(vertices, idVerticeDestinoAresta)) {
      vDestino = inicializaVertice(idVerticeDestinoAresta); // Criando novo vértice
      vertices[idVerticeDestinoAresta-1] = vDestino; // Adicionando o vértice no vetor de vértices
    } else {
      vDestino = vertices[idVerticeDestinoAresta-1]; // Pegando o vértice já existente
    }

    Aresta* a = inicializaAresta(i, vOrigem, vDestino, dist, velMedia);

    adicionaArestaVizinha(vOrigem, i); // Adicionando o id da aresta no vetor de arestas vizinhas do vértice de origem

    /* Adicionando a aresta no vetor, conforme elas aparecem no arquivo */
    arestas[i] = a;
  }
  
  return inicializaGrafo(vertices, arestas, numVertices, numArestas, idVerticeOrigem, idVerticeDestino);
}

void calculaMelhorRotaGrafo(Grafo* grafo, FILE* arquivoEntrada) {
  int idVerticeOrigem = 0, idVerticeDestino = 0, instanteDeTempo = 0;
  double velMedia = 0.0; // Nova velocidade média de uma aresta

  /* Variáveis que vão guardar o resultado */
  double dist[grafo->numVertices]; // Peso (tempo) da distancia da origem até o vértice
  int prev[grafo->numVertices]; // Guarda o id dos vértices anteriores

  aplicaAlgoritmoDijkstra(grafo, dist, prev);
  return;

  while (!chegouAoDestino(grafo)) {
    if (!feof(arquivoEntrada)) {
      fscanf(arquivoEntrada, "%d;%d;%d;%lf", &instanteDeTempo, &idVerticeOrigem, &idVerticeDestino, &velMedia);
    }

    aplicaAlgoritmoDijkstra(grafo, dist, prev);
    if (grafo->tempoPercorrido > instanteDeTempo) {
      recalculaPesosGrafo(grafo, idVerticeOrigem, idVerticeDestino, velMedia); // Recalcula os pesos das arestas do grafo
    }
  }
}

static Item makeItem(Vertice* v, double value) {
  Item item;
  id(item) = getIdVertice(v);
  value(item) = value;
  return item;
}

static void percorreUmVerticeGrafo(Grafo* grafo, int idVertice) {
  // grafo->tempoPercorrido += 
  // grafo->distanciaPercorrida += 
  grafo->idVerticesPercorridos[grafo->numVerticesPercorridos] = idVertice;
  grafo->numVerticesPercorridos++;
}

void aplicaAlgoritmoDijkstra(Grafo* grafo, double* dist, int* prev) {
  Pq* pQueue = PQ_init(grafo->numVertices); // Inicializa a fila de prioridade

  dist[grafo->idVerticeOrigem-1] = 0.0; // Distância da origem até a origem é 0
  prev[grafo->idVerticeOrigem-1] = UNDEFINED; // Vértice anterior não existe

  int i = 0;
  for (i = 0; i < grafo->numVertices; i++) {
    if (getIdVertice(grafo->vertices[i]) != grafo->idVerticeOrigem) {
      dist[i] = INFINITY; // Distância da origem até o vértice é infinito
      prev[i] = UNDEFINED; // Vértice anterior não existe
    }
    PQ_insert(pQueue, makeItem(grafo->vertices[i], dist[i])); // Insere o vértice na fila de prioridade
  }

  imprimePq(pQueue); // Debug

  /* Pra incrementar ao grafo depois */
  double pesoArestas[grafo->numArestas];
  double distArestas[grafo->numArestas];

  while (!PQ_empty(pQueue)) {
    Item item = PQ_delmin(pQueue);
    printf("id: %d, value: %lf\n", id(item), value(item));
    
    Vertice* u = grafo->vertices[id(item)-1];
    printf("del mim: Vertice u com id: %d\n", getIdVertice(u));

    for (i = 0; i < getNumVizinhosVertice(u); i++) {
      Aresta* a = grafo->arestas[getIdArestasVizinhasVertice(u)[i]];
      Vertice* v = getVerticeDestinoAresta(a);
      printf("Vertice v (destino da aresta) com id: %d\n", getIdVertice(v));

      double alt = dist[getIdVertice(u)-1] + getPesoAresta(a);
      printf("dist[getIdVertice(u)-1] = %.5lf + getPesoAresta(a) = %.5lf\n", dist[getIdVertice(u)-1], getPesoAresta(a));
      printf("alt: %lf\n", alt);


      printf("alt = %.5lf < dist[getIdVertice(v)-1] = %.5lf\n\n", alt, dist[getIdVertice(v)-1]);
      if (alt < dist[getIdVertice(v)-1]) {
        dist[getIdVertice(v)-1] = alt;
        prev[getIdVertice(v)-1] = getIdVertice(u);
        PQ_decrease_key(pQueue, getIdVertice(v), alt);
      }
    }
  }

  imprimePq(pQueue); // Debug
  PQ_finish(pQueue);

  for (i = 0; i < grafo->numVertices; i++) {
    printf("%lf ", dist[i]);
  }
  printf("\n");

  for (i = 0; i < grafo->numVertices; i++) {
    printf("%d ", prev[i]);
  }
  printf("\n");

  /* Determina o próximo vértice do melhor caminho */
  int proximoVertice = grafo->idVerticeDestino;
  int ant = proximoVertice;
  while (prev[proximoVertice-1] != UNDEFINED) {
    printf("%d ", proximoVertice);
    ant = proximoVertice;
    proximoVertice = prev[proximoVertice-1];
  }
  printf("\n");

  printf("prox: %d\n", ant);

  percorreUmVerticeGrafo(grafo, ant);
  

  printf("\n");

  /*
    Depois disso a função deve dar um passo para frente,ou seja, 
    trocar o vértice de origem do grafo para o próximo vértice do algoritmo.
    Depois disso ele deve adicionar o tempo q gastou com esse passo no campo tempoPercorrido,
    adicionar a distância percorrida no campo distanciaPercorrida e adicionar o id do vértice percorrido
    no campo de idVerticesPercorridos.
  */
}

int chegouAoDestino(Grafo* grafo) { return grafo->idVerticeOrigem == grafo->idVerticeDestino; }

void recalculaPesosGrafo(Grafo* grafo, int idVerticeOrigem, int idVerticeDestino, double velMedia) {
  int i = 0;
  for (i = 0; i < grafo->numArestas; i++) { // Encontrar a aresta a ser atualizada
    Aresta* a = grafo->arestas[i];
    if (
        getIdVertice(getVerticeOrigemAresta(a)) == idVerticeOrigem && 
        getIdVertice(getVerticeDestinoAresta(a)) == idVerticeDestino
    ) {
      setVelMediaAresta(a, velMedia); // Atualiza a velocidade média da aresta 
    }
  }
}

Grafo *inicializaGrafo(
  Vertice** v,
  Aresta** a,
  int numVertices,
  int numArestas,
  int idVerticeOrigem,
  int idVerticeDestino
) {
  Grafo* g = (Grafo*) malloc(sizeof(Grafo));
  g->vertices = v;
  g->arestas = a;
  g->numVertices = numVertices;
  g->numArestas = numArestas;
  g->idVerticeOrigem = idVerticeOrigem;
  g->idVerticeDestino = idVerticeDestino;
  g->tempoPercorrido = 0.0;
  g->distanciaPercorrida = 0.0;
  g->idVerticesPercorridos = (int*) calloc(numVertices, sizeof(int)); // Começa alocando com o número máximo de vértices
  g->numVerticesPercorridos = 0;
  return g;
}

void destroiGrafo(Grafo *g) {
  int i = 0;
  for (i = 0; i < g->numVertices; i++) {
    destroiVertice(g->vertices[i]);
  }
  free(g->vertices);
  for (i = 0; i < g->numArestas; i++) {
    destroiAresta(g->arestas[i]);
  }
  free(g->arestas);
  free(g->idVerticesPercorridos);
  free(g); 
}

void imprimeGrafo(Grafo *g) {
  printf("Grafo com %d vertices e %d arestas\n", g->numVertices, g->numArestas);
  printf("-----------------\n");
  int i = 0;
  for (i = 0; i < g->numVertices; i++) {
    imprimeVertice(g->vertices[i]);
  }
  printf("-----------------\n");
  for (i = 0; i < g->numArestas; i++) {
    imprimeAresta(g->arestas[i]);
  }
}

Vertice **getVerticesGrafo(Grafo *g) { return g->vertices; }

Aresta **getArestasGrafo(Grafo *g) { return g->arestas; }

int getNumVerticesGrafo(Grafo *g) { return g->numVertices; }

int getNumArestasGrafo(Grafo *g) { return g->numArestas; }

void setNumVerticesGrafo(Grafo *g, int numVertices) { g->numVertices = numVertices; }

void setNumArestasGrafo(Grafo *g, int numArestas) { g->numArestas = numArestas; }