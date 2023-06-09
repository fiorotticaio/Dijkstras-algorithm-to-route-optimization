#include "atualizacao.h"

struct atualizacao {
  double tempo;
  int idVerticeOrigem;
  int idVerticeDestino;
  double velMedia;
};

Atualizacao* inicializaAtualizacao(double tempo, int idVerticeOrigem, int idVerticeDestino, double velMedia) {
  Atualizacao* a = (Atualizacao*) malloc(sizeof(Atualizacao));
  a->tempo=tempo;
  a->idVerticeOrigem=idVerticeOrigem;
  a->idVerticeDestino=idVerticeDestino;
  a->velMedia=velMedia;
  return a;
}

