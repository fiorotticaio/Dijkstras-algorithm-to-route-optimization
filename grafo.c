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
  double** valores;
  double** distancias;
  double** velocidades;
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

  double matriz[numVertices][numVertices];
  double distancias[numVertices][numVertices];
  double velocidades[numVertices][numVertices];
  for(int j=0;j<numVertices;j++) {
    for(int k=0;k<numVertices;k++) {
      matriz[j][k]=0;
      distancias[j][k]=0;
      velocidades[j][k]=0;
    }
  }

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

    Aresta* a = inicializaAresta(vOrigem, vDestino, dist, velMedia);

    /* Adicionando a aresta no vetor, conforme elas aparecem no arquivo */
    arestas[i] = a;


    //======================================================================================//
    //======================================================================================//
    //======================================================================================//
    //======================================================================================//
    //======================================================================================//

  
    
    
    if(idVerticeOrigemAresta>idVerticeDestinoAresta) {
      matriz[idVerticeDestinoAresta-1][idVerticeOrigemAresta-1]=dist;
      matriz[idVerticeOrigemAresta-1][idVerticeDestinoAresta-1]=velMedia;
    }
    else {
      matriz[idVerticeOrigemAresta-1][idVerticeDestinoAresta-1]=dist;
      matriz[idVerticeDestinoAresta-1][idVerticeOrigemAresta-1]=velMedia;
    }


    distancias[idVerticeOrigemAresta-1][idVerticeDestinoAresta-1]=dist;
    velocidades[idVerticeOrigemAresta-1][idVerticeDestinoAresta-1]=velMedia;


  }

  return inicializaGrafo(vertices, arestas, numVertices, numArestas, idVerticeOrigem, idVerticeDestino, matriz, distancias, velocidades);
}

void calculaMelhorRotaGrafo(Grafo* grafo, FILE* arquivoEntrada) {
  int idVerticeOrigem = 0, idVerticeDestino = 0, instanteDeTempo = 0;
  double velMedia = 0.0; // Nova velocidade média de uma aresta

  // aplicaAlgoritmoDijkstra(grafo);

  while (!chegouAoDestino(grafo)) {
    if (!feof(arquivoEntrada)) {
      fscanf(arquivoEntrada, "%d;%d;%d;%lf", &instanteDeTempo, &idVerticeOrigem, &idVerticeDestino, &velMedia);
    }

    // aplicaAlgoritmoDijkstra(grafo);
    if (grafo->tempoPercorrido > instanteDeTempo) {
      recalculaPesosGrafo(grafo, idVerticeOrigem, idVerticeDestino, velMedia); // Recalcula os pesos das arestas do grafo
    }
  }
}

int distanciaMinima(double distancia[], int visitados[], int numVertices){
    int min=99999999, minPosicao;

    for (int i=0;i<numVertices;i++) {
      if (visitados[i]==0 && distancia[i]<=min) {
        min = distancia[i];
        minPosicao=i;
      }
    }

    return minPosicao;
}

// TODO: implementar essa função
void aplicaAlgoritmoDijkstra(Grafo* grafo) {

  int numVertices=getNumVerticesGrafo(grafo);
  double distancia[numVertices];
  int visitados[numVertices];
  int pai[numVertices];

  int matriz[numVertices][numVertices];

  // for(int i=0;i<numVertices;i++) {
  //   for(int j=0;j<numVertices;j++) {
  //     matriz[i][j]=getValorMatriz(grafo, i, j);
  //   }
  // }

  for(int i=0;i<numVertices;i++) {
    distancia[i]=99999999;
    visitados[i]=0;
    pai[i]=-1;
  }

  distancia[grafo->idVerticeOrigem-1]=0;

  printf("\n");
  for(int x=0;x<numVertices-1;x++) {
    int i=distanciaMinima(distancia, visitados, numVertices);
    visitados[i]=1;
    
    for(int j=0;j<numVertices;j++) {
      if(!visitados[j] && getValorDistancia(grafo, i, j) && distancia[i]!=99999999 && distancia[i]+getPesoMatriz(grafo, i, j)<distancia[j]) {
        distancia[j]=distancia[i]+getPesoMatriz(grafo, i, j);
        pai[j]=i;
      }
    }
  }

  for(int i=0;i<numVertices;i++) {
    printf("%d ", pai[i]+1);
  }
  printf("\n");

  for(int i=0;i<numVertices;i++) {
    printf("%.2lf ", distancia[i]*40);
  }
  printf("\n");

  int l=grafo->idVerticeDestino-1;
  while (l!=-1) {
    printf("%d ", l+1);
    l=pai[l];
  }
  printf("\n");

  /*
    dist[source] ← 0  // Initialization
    create vertex priority queue Q

    for each vertex v in Graph.Vertices:
      if v ≠ source
        dist[v] ← INFINITY // Unknown distance from source to v
        prev[v] ← UNDEFINED // Predecessor of v

      Q.add_with_priority(v, dist[v])

    while Q is not empty: // The main loop
      u ← Q.extract_min() // Remove and return best vertex
      for each neighbor v of u: // Go through all v neighbors of u
        alt ← dist[u] + Graph.Edges(u, v)
        if alt < dist[v]:
          dist[v] ← alt
          prev[v] ← u
          Q.decrease_priority(v, alt)
  */

  /*
    Depois disso a função deve dar um passo para frente,ou seja, 
    trocar o vértice de origem do grafo para o próximo vértice do algoritmo.
    Depois disso ele deve adicionar o tempo q gastou com esse passo no campo tempoPercorrido,
    adicionar a distância percorrida no campo distanciaPercorrida e adicionar o id do vértice percorrido
    no campo de idVerticesPercorridos.
  */
}

// TODO: implementar essa função
int chegouAoDestino(Grafo* grafo) {

}

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

  if(idVerticeOrigem>idVerticeDestino) {
    grafo->valores[idVerticeOrigem-1][idVerticeDestino-1]=velMedia;
  }
  else {
    grafo->valores[idVerticeDestino-1][idVerticeOrigem-1]=velMedia;
  }

  grafo->velocidades[idVerticeOrigem-1][idVerticeDestino-1]=velMedia;
}

Grafo *inicializaGrafo(
  Vertice** v,
  Aresta** a,
  int numVertices,
  int numArestas,
  int idVerticeOrigem,
  int idVerticeDestino,
  double matriz[numVertices][numVertices],
  double dist[numVertices][numVertices],
  double vel[numVertices][numVertices]
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
  
  g->valores = malloc(numVertices*sizeof(double*));
  g->distancias = malloc(numVertices*sizeof(double*));
  g->velocidades = malloc(numVertices*sizeof(double*));
  for(int i=0;i<numVertices;i++) {
    g->valores[i]=malloc(numVertices*sizeof(double));
    g->distancias[i]=malloc(numVertices*sizeof(double));
    g->velocidades[i]=malloc(numVertices*sizeof(double));
  }
  for(int i=0;i<numVertices;i++) {
    for(int j=0;j<numVertices;j++) {
      g->valores[i][j]=matriz[i][j];
      g->distancias[i][j]=dist[i][j];
      g->velocidades[i][j]=vel[i][j];
    }
  }

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
  for(i=0;i<g->numVertices;i++) {
    free(g->valores[i]);
  }
  for(i=0;i<g->numVertices;i++) {
    free(g->distancias[i]);
  }
  for(i=0;i<g->numVertices;i++) {
    free(g->velocidades[i]);
  }
  free(g->valores);
  free(g->distancias);
  free(g->velocidades);
  free(g->arestas);
  free(g->idVerticesPercorridos);
  free(g); 
}

void imprimeGrafo(Grafo *g) {
  // printf("Grafo com %d vertices e %d arestas\n", g->numVertices, g->numArestas);
  // printf("-----------------\n");
  // int i = 0;
  // for (i = 0; i < g->numVertices; i++) {
  //   imprimeVertice(g->vertices[i]);
  // }
  // printf("-----------------\n");
  // for (i = 0; i < g->numArestas; i++) {
  //   imprimeAresta(g->arestas[i]);
  // }
  for(int i=0;i<g->numVertices;i++) {
    for(int j=0;j<g->numVertices;j++) {
      printf("%.2lf ", g->distancias[i][j]);
    }
    printf("\n");
  }
}

Vertice **getVerticesGrafo(Grafo *g) { return g->vertices; }

Aresta **getArestasGrafo(Grafo *g) { return g->arestas; }

int getNumVerticesGrafo(Grafo *g) { return g->numVertices; }

int getNumArestasGrafo(Grafo *g) { return g->numArestas; }

double getValorMatriz(Grafo* g, int i, int j) {return g->valores[i][j];}

double getValorDistancia(Grafo* g, int i, int j) {return g->distancias[i][j];}

double getPesoMatriz(Grafo* g, int i, int j) { return g->distancias[i][j]/g->velocidades[i][j]; }

void setNumVerticesGrafo(Grafo *g, int numVertices) { g->numVertices = numVertices; }

void setNumArestasGrafo(Grafo *g, int numArestas) { g->numArestas = numArestas; }

int setValorMatriz(Grafo* g, int i, int j, double valor) { g->valores[i][j]=valor; }