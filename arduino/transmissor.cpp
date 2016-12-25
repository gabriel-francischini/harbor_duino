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
/*@NPPBookmarkiniciarTransmissao(void)*/ 
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
/*@NPPBookmarkprocessarTransmissao(void)*/
// $nota Reimplementar a funcao processarTransmissao

byte marcadorAtual = 0;

void processarTransmissao(void){
  
  
  // Caso haja alguma byte na porta serial
  // esperando ser lido, processe-o
  if(Serial.available() > 0){
	
	
	// Lê o byte que estava esperando
	// ser lido e o coloca em byteLido
	byte byteLido = Serial.read();
	
	// Se o byteLido for um marcador,
	// o marcador atual passa a ser ele
	if(tipoToken(byteLido) == Marcador){
		marcadorAtual = byteLido;
		
		// Retorna para não uar tempo e
		// processamento desnecessário
		return;
	}
	
	// Grava o byte no buffer para ser
	// processado em outros locais
	gravarBuffer(byteLido);
	
	// Se esse byte indicava o fim da mensagem
	if(byteLido == FTM) 
		
		// Então processe a mensagem que foi recebida
		__processarTransmissao();
  }
}

//! Envia uma informação para o servidor central
/*! Envia o ponteiro indicado por *ponteiro 
 * para o servidor via serial. 
  * \see  delayResposta, FTM, enviar(byte *ponteiro, int tamanho) */
/*@NPPBookmarkenviar(byte *)*/
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
/*@NPPBookmarkenviar(byte *,int)*/
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
/*@NPPBookmarkgravarBuffer(byte)*/
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

//! Função simples para enviar um erro à interface gráfica/raspberry
/*@NPPBookmarkenviarErro(byte)*/
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
/*@NPPBookmark__processarTransmissao(void)*/
// $nota reescrever a funcao __processarTransmissao
void __processarTransmissao(void){
	
	
}

/*@NPPBookmarkexecutar(byte *, byte *)*/
// $nota rever a funcao executar
void executar(byte *inicio, byte *fim){
	
}

/*@NPPBookmarkzerar(byte *, byte)*/
void zerar(byte *array, byte tamanho){
	
	for(byte contador; contador < tamanho; contador++) 
		*(array+contador) = 0;
	
}

/*@NPPBookmarkseind(byte, byte)*/
void seind(byte value,byte times){
	
	for(byte x = 0; x < times; x++)
		enviar(&value,1);
	delay(delayResposta);
}

//! Função que diz se o que está no buffer é válido ou não
/*! Chamada normalmente por processarTransmissao(void), esta
 * função analiza se os comandos no buffer *__buffer* são válidos.
 * \see __buffer, processarTransmissao(void), gravarBuffer(byte) */
 // $nota escrever esta funcao
bool comandoValido(byte marcador){
	
}

/*@NPPBookmarktipoToken(byte *)*/
token tipoToken(byte *Token){
	
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
