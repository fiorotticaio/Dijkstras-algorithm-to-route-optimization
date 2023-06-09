#include "grafo.h"

struct grafo {
  Vertice** vertices;
  Aresta** arestas;
  Atualizacao** atualizacoes; 
  int numVertices;
  int numArestas;
  int idVerticeOrigem;
  int idVerticeDestino;
  double tempoPercorrido;
  double distanciaPercorrida;
  int* idVerticesPercorridos;
  int numVerticesPercorridos;
  int numAtualizacoes;
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

  double instanteTempo, dist;
  int idVerticeOrigemMudanca, idVerticeDestinoMudanca;

  /* Essa parte serve para calcular quantas alteraçoes de tempo serão feitas no código */
  long saved = ftell(arquivoEntrada);
  int count=0;
  while(!feof(arquivoEntrada)) {
    fscanf(arquivoEntrada, "%lf;%d;%d;%lf", &instanteTempo, &idVerticeOrigemMudanca, &idVerticeDestinoMudanca, &dist);
    count++;
  }
  fseek(arquivoEntrada, saved, SEEK_SET);

  Atualizacao** att = (Atualizacao**) calloc(count, sizeof(Atualizacao*));

  /* Funçao para criar e armazenar todas as alteraçoes que serao feitas durante o percurso */
  for(int i=0;i<count;i++) {
    fscanf(arquivoEntrada, "%lf;%d;%d;%lf", &instanteTempo, &idVerticeOrigemMudanca, &idVerticeDestinoMudanca, &dist);
    att[i]=inicializaAtualizacao(instanteTempo, idVerticeOrigemMudanca, idVerticeDestinoMudanca, dist);
  }
  
  return inicializaGrafo(vertices, arestas, numVertices, numArestas, idVerticeOrigem, idVerticeDestino, att, count);
}

/* Funçao que  */
void checaAtualizacoes(Grafo* grafo, int attAtual) {
  for(int i=attAtual;i<grafo->numAtualizacoes;i++) {
    if(grafo->tempoPercorrido>retornaTempoAtualizacao(grafo->atualizacoes[i])) {
      recalculaPesosGrafo(grafo, retornaIdVerticeOrigemAtualizacao(grafo->atualizacoes[i]), retornaIdVerticeDestinoAtualizacao(grafo->atualizacoes[i]), retornaVelMediaAtualizacao(grafo->atualizacoes[i]));
      attAtual++;    
    }
    else {break;}
  }
}

void calculaMelhorRotaGrafo(Grafo* grafo, FILE* arquivoEntrada) {
  int idVerticeOrigem = 0, idVerticeDestino = 0, instanteDeTempo = 0, attAtual = 0;
  double velMedia = 0.0; // Nova velocidade média de uma aresta

  /* Variáveis que vão guardar o resultado do algoritimo */
  double tempo[grafo->numVertices]; // tempo da origem até o vértice
  double dist[grafo->numVertices]; // Distancia da origem até o vértice
  int caminho[grafo->numVertices]; // Guarda o id dos vértices anteriores

  /* Verifica se houve alguma alteraçao de velocidade e aplica o algoritmo de Dijkstra para encontrar o melhor caminho */
  do {
    checaAtualizacoes(grafo, attAtual);
    aplicaAlgoritmoDijkstra(grafo, tempo, dist, caminho);
  } while(!chegouAoDestino(grafo));
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

void aplicaAlgoritmoDijkstra(Grafo* grafo, double* tempo, double* dist, int* caminho) {
  Pq* pQueue = PQ_init(grafo->numVertices); // Inicializa a fila de prioridade

  /* Inicialização das variáveis para a origem */
  tempo[grafo->idVerticeOrigem-1] = 0.0; // Tempo da origem até a origem é 0
  dist[grafo->idVerticeOrigem-1] = 0.0; // Distância da origem até a origem é 0
  caminho[grafo->idVerticeOrigem-1] = UNDEFINED; // Vértice anterior não existe

  int i = 0;
  for (i = 0; i < grafo->numVertices; i++) {
    if (getIdVertice(grafo->vertices[i]) != grafo->idVerticeOrigem) {
      tempo[i] = INFINITY; // Tempo da origem até o vértice é infinito
      dist[i] = INFINITY; // Distância da origem até o vértice é infinito
      caminho[i] = UNDEFINED; // Vértice anterior não existe
    }
    PQ_insert(pQueue, makeItem(grafo->vertices[i], tempo[i])); // Insere o vértice na fila de prioridade
  }

  while (!PQ_empty(pQueue)) {
    Item item = PQ_delmin(pQueue);
    Vertice* u = grafo->vertices[id(item)-1]; // Pega o vértice relacionado ao item removido da fila

    for (i = 0; i < getNumVizinhosVertice(u); i++) {
      Aresta* a = grafo->arestas[getIdArestasVizinhasVertice(u)[i]]; // Pega uma das arestas conectadas ao vértice
      Vertice* v = getVerticeDestinoAresta(a); // Pega o vértice de destino da aresta (vizinho de u)

      double alt = tempo[getIdVertice(u)-1] + getPesoAresta(a); // Novo tempo para se deslocar de até v
      double alt2 = dist[getIdVertice(u)-1] + getDistAresta(a); // Nova distância para se deslocar de até v

      if (alt < tempo[getIdVertice(v)-1]) { // Se o novo tempo for menor que o anteriror
        tempo[getIdVertice(v)-1] = alt; // Atualiza o novo tempo
        dist[getIdVertice(v)-1] = alt2; // Atualiza a nova distância
        caminho[getIdVertice(v)-1] = getIdVertice(u); // Salva o id do vértice anterior
        PQ_decrease_key(pQueue, getIdVertice(v), alt); // Atualiza o valor do vértice na fila de prioridade
      }
    }
  }

  PQ_finish(pQueue);

  /* Determina o próximo vértice do melhor caminho gerado */
  int ultimoVertice = grafo->idVerticeDestino;
  int proxVertice = ultimoVertice;
  while (caminho[ultimoVertice-1] != UNDEFINED) {
    proxVertice = ultimoVertice;
    ultimoVertice = caminho[ultimoVertice-1];
  }

  percorreUmVerticeGrafo(grafo, proxVertice, tempo[proxVertice-1], dist[proxVertice-1]);
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
  fprintf(arq, "\n%lf\n", (grafo->distanciaPercorrida)/1000);

  /* Imprimindo o tempo de percurso */
  int horas = (int) (grafo->tempoPercorrido/3600);
  int minutos = (int) ((grafo->tempoPercorrido - horas*3600)/60);
  double segundos = grafo->tempoPercorrido - horas*3600 - minutos*60;
  fprintf(arq, "%02d:%02d:%.15lf\n", horas, minutos, segundos);
}

Grafo *inicializaGrafo(
  Vertice** v,
  Aresta** a,
  int numVertices,
  int numArestas,
  int idVerticeOrigem,
  int idVerticeDestino,
  Atualizacao** att,
  int count
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
  g->atualizacoes = att;
  g->numAtualizacoes = count;

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