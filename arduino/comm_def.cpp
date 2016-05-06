//! \file comm_def.h
#ifndef __COMM_DEF_CPP
#define __COMM_DEF_CPP

#include "Arduino.h"
#include "comm_def.h"

//! Buffer para funcionamento interno da comunicação
/*! Este buffer guarda os últimos bytes recebidos, a fim
 * de interpretá-los. Seu valor representa uma das limitações
 * para a comunicação com o servidor.
 * Não há limites para o envio de informações. 
 * \see gravarBuffer(byte), MAX_MENSSAGEM*/
byte __buffer[MAX_MENSSAGEM];

//! Ponteiro para funcionamento interno do buffer de comunicação
/*! Indica o endereço de memória do buffer.
 * \see __buffer, gravarBuffer(byte), MAX_MENSSAGEM*/
byte *ponteiroBuffer = &__buffer[0];

//! Índice para funcionamento interno da comunicação
/*! Indica quantos bytes já foram escritos no buffer, para
 * impedir que se acesse uma memória indevida, já que em
 * C/C++ não há esse tipo de checagem. 
 * \see gravarBuffer(byte), processarTransmissao(void), 
 * __processarTransmissao(void), tipoToken(byte *) */
byte indiceBuffer;

#endif
