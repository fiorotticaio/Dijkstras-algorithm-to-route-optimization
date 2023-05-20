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
  Grafo* grafo = leGrafo(argv[1]);
  imprimeGrafo(grafo); // Debug


  /*============ Aplicação do algoritmo de Dijkstra ============*/





  /*============ Liberação de memória ============*/
  destroiGrafo(grafo);

  return 0;
}