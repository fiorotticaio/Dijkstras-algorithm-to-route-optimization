#include <stdio.h>
#include "vertice.h"
#include "aresta.h"
#include "grafo.h"

int main(int argc, char** argv) {
  /**
   * @brief Significado de cada parâmetro:
   * argv[0] = ./trab2
   * argv[1] = nome_arquivo_entrada
   * argv[2] = nome_arquivo_saida
   */

  if (argc < 3) {
    printf("Use: ./trab2 <nome_arquivo_entrada> <nome_arquivo_saida>\n");
    return 1; 
  }

  /*============ Leitura dos dados de entrada ============*/
  FILE* arquivoEntrada = fopen(argv[1], "r");
  if (!arquivoEntrada) {
    printf("Erro ao abrir arquivo de entrada em %s\n", argv[1]);
    exit(1);
  }

  Grafo* grafo = leGrafo(arquivoEntrada);
  imprimeGrafo(grafo); // Debug

  aplicaAlgoritmoDijkstra(grafo);

  /*============ Aplicação do algoritmo de Dijkstra ============*/
  calculaMelhorRotaGrafo(grafo, arquivoEntrada);
  

  /*============ Liberação de memória ============*/
  fclose(arquivoEntrada);
  destroiGrafo(grafo);

  return 0;
}