#ifndef ATUALIZACAO_H
#define ATUALIZACAO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct atualizacao Atualizacao;

Atualizacao* inicializaAtualizacao(double tempo, int idVerticeOrigem, int idVerticeDestino, double velMedia);
double retornaTempoAtualizacao(Atualizacao* att);
int retornaIdVerticeOrigemAtualizacao(Atualizacao* att);
int retornaIdVerticeDestinoAtualizacao(Atualizacao* att);
double retornaVelMediaAtualizacao(Atualizacao* att);

#endif // ATUALIZACAO_H