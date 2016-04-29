#ifndef __TRANSMISSAO__
#define __TRANSMISSAO__

#include "Arduino.h"

// Função responsável pelo código do setUp() referente
// à comunicação serial/wifi
void iniciarTransmissao();


void processarTransmissao();
void __processarTransmissao();
void enviar(int informacao);


// Tabela de comandos
#define IT 100 // Início de Transmissão
#define IC 101 // Início de Cabeçalho
#define ITex 102 // Início de Texto
#define MD 103 // Modo de Dados
#define RMD 104 // Retorno do Modo de Dados ao modo normal
#define FT 105 // Fim de Transmissão

#endif
