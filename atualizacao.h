#ifndef ATUALIZACAO_H
#define ATUALIZACAO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct atualizacao Atualizacao;

/// @brief Inicializa um tipo Atualização
/// @param tempo 
/// @param idVerticeOrigem 
/// @param idVerticeDestino 
/// @param velMedia 
/// @return Ponteiro para atualização alocado
Atualizacao* inicializaAtualizacao(double tempo, int idVerticeOrigem, int idVerticeDestino, double velMedia);

/// @brief Retorna o campo de Tempo dentro de Atualização
/// @param att 
/// @return Campo Tempo
double retornaTempoAtualizacao(Atualizacao* att);

/// @brief Retorna o campo de ID do seu vértice de origem dentro de Atualização
/// @param att 
/// @return Campo ID do seu vértice de origem
int retornaIdVerticeOrigemAtualizacao(Atualizacao* att);

/// @brief Retorna o campo de ID do seu vértice de destino dentro de Atualização
/// @param att 
/// @return Campo ID do seu vértice de destino
int retornaIdVerticeDestinoAtualizacao(Atualizacao* att);

/// @brief Retorna o campo de velocidade média dentro de Atualização
/// @param att 
/// @return Campo velocidade média 
double retornaVelMediaAtualizacao(Atualizacao* att);

#endif // ATUALIZACAO_H