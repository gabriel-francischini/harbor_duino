/*! \file transmissor.h Arquivo responsável pela implementação de códigos de comunicação.
 * Compõe-se basicamente de uma série de funções e seus algoritmos, relativos à comunição. */
 
#include "Arduino.h"
#include "transmissor.h"

//! Função para abrir a comunicação de porta serial
/*! Basicamente, esta função abre a comunicação com a porta
 * serial numa velocidade de 9600 bits por segundo, define
 * as variáveis e outros itens necessários ao uso da comunicação
 * serial e retorna. 
 * \see processarTransmissao(), enviar(byte *ponteiro) */ 
void iniciarTransmissao(void){
  
  // Abre a serial com a velocidade de 9600
  Serial.begin(9600);
  
  // Código necessário para alguns arduinos
  while (!Serial){;} 

}

//! Impede a parada da comunicação em longos cálculos
/*! O seu maior uso é para momentos onde um grande
 * loop tem que ser executado, onde poderia haver uma demora
 * maior na comunicação, eventualmente levando a 
 * algum prejuízo. **Também é incluído no loop() principal** 
 * \see iniciarTransmissao(void), MAX_MENSSAGEM, gravarBuffer(byte), 
 * __processarTransmissao(void) */
void processarTransmissao(void){
  if(Serial.available() > 0){
	
	byte byteLido = Serial.read();
	gravarBuffer(byteLido);
	//enviar(&byteLido, 1);
	//delay(1000);
	
	
	if(byteLido == FTM) __processarTransmissao();
  }
}

//! Envia uma informação para o servidor central
/*! Envia o ponteiro indicado por *ponteiro 
 * para o servidor via serial. 
  * \see  delayResposta, FTM, enviar(byte *ponteiro, int tamanho) */
void enviar(byte *ponteiro){

	for(;*ponteiro != FTM;ponteiro++){
		Serial.write(*ponteiro);
		delay(delayResposta);
	}
	
	Serial.write(FTM);
	delay(delayResposta);
}

//! Envia uma informação de tamanho `tamanho` para o servidor central
/*! Envia o ponteiro indicado por *ponteiro 
 * para o servidor via serial. 
 * \see enviar(byte *ponteiro), delayResposta*/
void enviar(byte *ponteiro, int tamanho){

  for(int contador;contador < tamanho;ponteiro++, contador++){
	  Serial.write(*ponteiro);
	  delay(delayResposta);
  }
}

//! Função interna para gravar informação no buffer
/*! Grava a informação `valor` no buffer de histórico de menssagem
 * , que normalmente grava somenta as mensagens recebidas.
 * \param valor Byte a ser escrito no buffer 
 * \see __buffer, byteAtual, indiceBuffer, enviar(byte *ponteiro) */
void gravarBuffer(byte valor){

	if(indiceBuffer < MAX_MENSSAGEM){
		*(byteAtual) = valor;
		indiceBuffer += 1;
	}
	else {
		byte erro[] { ITM, ICB, ITX, AVS, EMD, 1, SMD, FTM };
		enviar(&erro[0]);
		indiceBuffer = 0;
		gravarBuffer(valor);
	}
	
}

void enviarErro(byte erro){
	byte mensagemErro[] { ITM, ICB, ITX, AVS, EMD, erro, SMD, FTM };
	enviar(&mensagemErro[0]);
		
}

//! Função interna responsável por interpretar a comunicação com o servidor
/*! Esta função é chamada quando uma mensagem completa é transmitida.
 * Isto é, ela é chamada quando um Fim de Transmissão (FTM) acaba de ser
 * escrito ao buffer, para que esta mensagem inteira seja interpretada e processada.
 * É ela que define as reações do arduino para cada mensagem, e como cada valor
 * deve ser tratado. 
 * \see ponteiroBuffer, processarTransmissao, tipoToken(byte *token) */
void __processarTransmissao(void){
	
	seind(0,8);
	
	byte marcadorAtual = 0;
	byte *comandoInicio = 0;
	byte *comandoFim = 0;
	byte *marcadorInicio = ponteiroBuffer;
	byte *marcadorFim = 0;
	byte *pontoAtual = ponteiroBuffer;
	
	for(;*pontoAtual != ITX;pontoAtual++){
		
		seind(1,8);
		seind(*pontoAtual,8);
		
		
		if(tipoToken(pontoAtual) == Marcador){
		
			seind(2,8);
	
			marcadorFim = pontoAtual;
			// Inserir comando de interpretação de cabeçalhos
			marcadorInicio = marcadorFim;
		}
	}
	
	
	
	for(; *(pontoAtual-1) != FTM ;pontoAtual++){
		
		seind(3,8);
		seind(*pontoAtual,8);
		
		if(*pontoAtual == EMD){
			
			do{
				pontoAtual++;
			
			seind(4,8);
			seind(*pontoAtual,8);
			
			}while(*pontoAtual != SMD);
		}
		else if( (*(pontoAtual-1) == ITX) && (tipoToken(pontoAtual) == Comando) ){
			
			seind(5,8);
			seind(*pontoAtual,8);
			
			marcadorInicio = pontoAtual;
		}
		else if(tipoToken(pontoAtual) == Comando || *pontoAtual == FTM){
			
			seind(6,8);
			seind(*pontoAtual,8);
			
			marcadorFim = pontoAtual;
			executar(marcadorInicio, marcadorFim);
			marcadorInicio = marcadorFim;
		}
		
	}
	
	if(marcadorFim == 0){
		
		seind(7,8);
		
		//seind(pontoAtual,2);
		seind(*pontoAtual,2);
		//seind(marcadorInicio,2);
		seind(*marcadorInicio,2);
		
		executar(marcadorInicio, pontoAtual);
	}
	
	zerar(&buffer[0], MAX_MENSSAGEM);
}



token tipoToken(byte *Token){
	
	seind(8,4);
	
	switch(*Token){
		case ITM:
		case FTM:
		case ICB:
		case ITX:
			//enviarErro(Marcador+10);
			return Marcador;
			break;
		
		case EMD:
		case SMD:
			//enviarErro(Valor+10);
			return Valor;
			break;
		
		case PIN:
			//enviarErro(Modificador+10);
			return Modificador;
			break;
		
		case SNM:
		case ERR:
		case AVS:
		case QAL:
			//enviarErro(Comando+10);
			return Comando;
			break;
		
		default:
			//enviarErro(Desconhecido+10);
			return Desconhecido;
			break;
	}
}


void executar(byte *inicio, byte *fim){
	
	seind(9,8);
	seind(*inicio,4);
	//seind(inicio,4);
	seind(*fim,4);
	//seind(fim,4);
	
	byte numeroParametros = 0;
	byte *pontoAtual = inicio;
	
	for(pontoAtual = inicio; pontoAtual < fim; pontoAtual++){
		
		seind(10,8);
		seind(*pontoAtual,4);
		//seind(pontoAtual, 4);
		
		if(*pontoAtual == SMD){
			
			seind(11,8);
			seind(*pontoAtual,4);
			
			numeroParametros++;
		}
		
	}	
	if(numeroParametros > maxParametros) return;
	
	
	seind(12,8);
	
	byte codigoEstado = 0;
	int __resultadoAtual = 0;
	int __operando1 = 0;
	int __operando2 = 0;
	
	int *resultadoAtual = &__resultadoAtual;
	int *operando1 = &__operando1;
	int *operando2 = &__operando2;
	
	
	byte *modificadorEncontrado = 0;
	
	for(pontoAtual = inicio; pontoAtual < fim; pontoAtual++){
			
			seind(13,8);
			seind(*pontoAtual,8);
			
		if(*pontoAtual == EMD){
			while(*pontoAtual != SMD){
				seind(14,4);
				seind(*pontoAtual,8);
				
				pontoAtual++;
				
				switch(codigoEstado){
					
					case 0:
						*operando1 = *pontoAtual;
						codigoEstado = 1;
					break;
					
					case 1:
						*operando1 = *operando1 * 100;
						*operando1 += *pontoAtual;
					break;
					
					case 2:
						*operando2 = *pontoAtual;
						codigoEstado = 3;
					break;
					
					case 3:
						*operando2 = 100 * (*operando2);
						*operando2 += *pontoAtual;
					break;
				
				}
			}
		}
		
		
		
		if(modificadorEncontrado == 0){
			if(tipoToken(pontoAtual) == Modificador)
					
					seind(15,4);
					seind(*pontoAtual,4);
				
				modificadorEncontrado = pontoAtual;
		}
		else if(modificadorEncontrado != 0){
			
			seind(16,4);
			seind(*pontoAtual,4);
			
			int *parametro;
			if(codigoEstado == 1) parametro = operando1;
			else if(codigoEstado == 3) parametro = operando2;
			//else return;
			
			for(byte *modificadorAtual = pontoAtual; tipoToken(modificadorAtual) == Modificador ; modificadorAtual++){
					
					seind(17,8);
					seind(*modificadorAtual,4);
					
					switch(*modificadorAtual){
						
						case PIN:
							*parametro = digitalRead(*parametro);
						break;
					}
			}
			
			modificadorEncontrado = 0;
		}
		
		if(codigoEstado == 1) {codigoEstado = 2;}
		if(codigoEstado == 3){
			
			seind(18,8);
			seind(*inicio,4);
			seind(*operando1,4);
			seind(*operando2,4);
			seind(*resultadoAtual,4);
			
			operar(*inicio, operando1, operando2, resultadoAtual);
			
			operando1 = &__operando1;
			*operando1 = *resultadoAtual;
			
			operando2 = &__operando2;
			*operando2 = 0;
			
			resultadoAtual = &__resultadoAtual;
			codigoEstado = 2;
		}
	}
	
}

void operar(byte comando, int *operando1, int *operando2, int *resultado){
	seind(19,8);
	
	switch(comando){
		
		case SNM:
			*operando1 = *operando2;
		break;
		
		case QAL:
			byte resp[] =
			{ ITM, ICB, ITX, RSP, EMD, (byte) *operando1, SMD, EMD, 0, SMD, FTM };
			enviar(&resp[0]);
		break;
		
	}
}

void zerar(byte *array, byte tamanho){
	
	for(byte contador; contador < tamanho; contador++) 
		*(array+contador) = 0;
	
}


void seind(byte value,byte times){
	
	/*for(byte x = 0; x < times; x++)
		enviar(&value,1);
	delay(delayResposta);*/
}
