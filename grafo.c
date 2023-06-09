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

  /* Variáveis que vão guardar o resultado do algoritimo */
  double temp[grafo->numVertices]; // tempo da origem até o vértice
  double dist[grafo->numVertices]; // Distancia da origem até o vértice
  int prev[grafo->numVertices]; // Guarda o id dos vértices anteriores

  aplicaAlgoritmoDijkstra(grafo, temp, dist, prev);

  while (!chegouAoDestino(grafo)) {
    // Atualizações
    aplicaAlgoritmoDijkstra(grafo, temp, dist, prev);
  }
}

static Item makeItem(Vertice* v, double value) {
  Item item;
  id(item) = getIdVertice(v);
  value(item) = value;
  return item;
}

static void percorreUmVerticeGrafo(Grafo* grafo, int idVertice, double tempo, double distancia) {
  grafo->tempoPercorrido += tempo;
  grafo->distanciaPercorrida += distancia;
  grafo->idVerticesPercorridos[grafo->numVerticesPercorridos] = idVertice;
  grafo->numVerticesPercorridos++;
  grafo->idVerticeOrigem = idVertice;
}

void aplicaAlgoritmoDijkstra(Grafo* grafo, double* temp, double* dist, int* prev) {
  Pq* pQueue = PQ_init(grafo->numVertices); // Inicializa a fila de prioridade

  /* Inicialização das variáveis para a origem */
  temp[grafo->idVerticeOrigem-1] = 0.0; // Tempo da origem até a origem é 0
  dist[grafo->idVerticeOrigem-1] = 0.0; // Distância da origem até a origem é 0
  prev[grafo->idVerticeOrigem-1] = UNDEFINED; // Vértice anterior não existe

  int i = 0;
  for (i = 0; i < grafo->numVertices; i++) {
    if (getIdVertice(grafo->vertices[i]) != grafo->idVerticeOrigem) {
      temp[i] = INFINITY; // Tempo da origem até o vértice é infinito
      dist[i] = INFINITY; // Distância da origem até o vértice é infinito
      prev[i] = UNDEFINED; // Vértice anterior não existe
    }
    PQ_insert(pQueue, makeItem(grafo->vertices[i], temp[i])); // Insere o vértice na fila de prioridade
  }

  while (!PQ_empty(pQueue)) {
    Item item = PQ_delmin(pQueue);
    Vertice* u = grafo->vertices[id(item)-1]; // Pega o vértice relacionado ao item removido da fila

    for (i = 0; i < getNumVizinhosVertice(u); i++) {
      Aresta* a = grafo->arestas[getIdArestasVizinhasVertice(u)[i]]; // Pega uma das arestas conectadas ao vértice
      Vertice* v = getVerticeDestinoAresta(a); // Pega o vértice de destino da aresta (vizinho de u)

      double alt = temp[getIdVertice(u)-1] + getPesoAresta(a); // Novo tempo para se deslocar de até v
      double alt2 = dist[getIdVertice(u)-1] + getDistAresta(a); // Nova distância para se deslocar de até v

      if (alt < temp[getIdVertice(v)-1]) { // Se o novo tempo for menor que o anteriror
        temp[getIdVertice(v)-1] = alt; // Atualiza o novo tempo
        dist[getIdVertice(v)-1] = alt2; // Atualiza a nova distância
        prev[getIdVertice(v)-1] = getIdVertice(u); // Salva o id do vértice anterior
        PQ_decrease_key(pQueue, getIdVertice(v), alt); // Atualiza o valor do vértice na fila de prioridade
      }
    }
  }

  PQ_finish(pQueue);

  /* Determina o próximo vértice do melhor caminho gerado */
  int ultimoVertice = grafo->idVerticeDestino;
  int proxVertice = ultimoVertice;
  while (prev[ultimoVertice-1] != UNDEFINED) {
    proxVertice = ultimoVertice;
    ultimoVertice = prev[ultimoVertice-1];
  }

  percorreUmVerticeGrafo(grafo, proxVertice, temp[proxVertice-1], dist[proxVertice-1]);
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

void imprimeResultadoGrafo(Grafo* grafo, FILE* arq) {
  /* Imprimindo o caminho do percurso */
  int i = 0;
  for (i = 0; i < grafo->numVerticesPercorridos; i++) {
    fprintf(arq, "%d", grafo->idVerticesPercorridos[i]);
    if (i != grafo->numVerticesPercorridos-1) fprintf(arq, ";");
  }
  printf("\n");

  /* Imprimindo a distância (em km) de percurso */
  fprintf(arq, "\n%.2lf\n", (grafo->distanciaPercorrida)/1000);

  /* Imprimindo o tempo de percurso */
  int horas = (int) (grafo->tempoPercorrido/3600);
  int minutos = (int) ((grafo->tempoPercorrido - horas*3600)/60);
  double segundos = grafo->tempoPercorrido - horas*3600 - minutos*60;
  fprintf(arq, "%02d:%02d:%.1lf", horas, minutos, segundos);
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

  /* O primeiro vértice percprrido é a própria origme */
  g->idVerticesPercorridos[g->numVerticesPercorridos] = idVerticeOrigem;
  g->numVerticesPercorridos++;
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