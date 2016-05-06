/*! \file transmissor.h Biblioteca responsável pela comunicação serial com o servidor */

#ifndef __TRANSMISSAO__
#define __TRANSMISSAO__

#include "Arduino.h"
#include "comm_def.h"

void iniciarTransmissao(void);
void processarTransmissao(void);
void __processarTransmissao(void);
void enviar(byte *ponteiro);
void gravarBuffer(byte valor);
void enviar(byte *ponteiro, int tamanho);
token tipoToken(byte *Token);
void executar(byte *inicio, byte *fim);
void operar(byte comando, int *operando1, int *operando2, int *resultado);
void zerar(byte *array, byte tamanho);
void enviarErro(byte erro);
void seind(byte value,byte times);
#endif
