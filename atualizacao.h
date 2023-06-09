#ifndef ATUALIZACAO_H
#define ATUALIZACAO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct atualizacao Atualizacao;

Atualizacao* inicializaAtualizacao(double tempo, int idVerticeOrigem, int idVerticeDestino, double velMedia);

#endif // ATUALIZACAO_H