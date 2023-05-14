#include <stdio.h>

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
  
  return 0;
}