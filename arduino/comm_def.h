/*! \file comm_def.h Guardas as definições de comandos partilhadas tanto pelo servidor quanto pelo arduino. É basicamente as "palavras" pelas quais ambos os lados se comunicam. */

#ifndef __COM_DEF
#define __COM_DEF

#define MAX_MENSSAGEM 80
//!< Indica o tamanho máximo que uma mensagem inteira pode ter (em comandos)

// Tabela de comandos

#define ITM 100 
//!< Marcador de início de transmissão
/*!< Representa que a infomação a seguir é considerada parte
 * da transmissão, já que existe a possibilidade de interferência
 * do meio pelo qual é feita a comunicação. */

#define ICB 101 
//!< Início de Cabeçalho
/*!< É um marcador para indicar que os bytes a seguir devem
 * ser condirados como um cabeçalho, e não como comandos */

#define ITX 102 
//!< Início de Texto
/*!< Indica o fim do cabeçalho e o inicio da informação 
 * propriamente dita, como comandos e valores de variáveis */

#define EMD 103 
//!< Entrar no Modo de Dados
/*!< Os valores entre EMD e SMD são considerados valores absolutos, sem qualquer interpretação. Seria como argumentos/parametros dos comandos. */

#define SMD 104 
//!< Sair do Modo de Dados
/*!< Indica que os próximos bytes devem ser interpretados como comandos, e não mais como valores absolutos. */

#define FTM 105 
//!< Fim de Transmissão
/*!< Marca o fim de uma mensagem entre o servidor e o arduino. */

#define PIN 106
//!< Indica o valor de um PINo
/*!< Seguido de EMD (pino) SMD, indica que o valor absoluto a seguir representa uma das portas do arduino. */

#define SNM 107
//!< Sinônimo, equivalente a, igual a
/*!< Indica que os dois valores a seguir (normalmente uma váriavel e um número, ou um número e uma variável) são iguais. Cada qual entre EMD e SMD, respectivamente. 
 * Exemplo: 
 @code
 ITM ICB ITX 
 SNM
 PIN EMD 5 SMD  
     EMD 7 SMD 
 FTM @endcode Indica que o valor do pino 5 é 7.  */

#define ERR 108
//!< Indica um erro que aconteceu e aborta o que tentou fazer
/*!< Serve para indicar que um erro severo e perigoso ocorreu 
 * (indicando qual) e desistindo de fazer o que estava fazendo
 * antes. */
 
#define AVS 109
//!< Emite um aviso, como algum pequeno erro ou algo similar
/*!< Tal "erro" deve ser algo tolerável (i.e. não oferece riscos
 * ao programa ou operadores), mas é um incômodo 
 * incoveniente */
 
#define QAL 110
//!< Pede para enviar o valor de uma variável ou porta
/*!< É um que toma dois operadores, sendo um o valor
 * do que se quer saber e o outro um zero para que o primeiro
 * não seja ignorado. Numa lista de valores basta adicionar
 * um único zero no final, não necessitando adicionar um zero
 * após cada valor. */
 
#define RSP 111
//!< Indica uma resposta a um QAL.
 
extern byte __buffer[MAX_MENSSAGEM];
extern byte *ponteiroBuffer;
extern byte indiceBuffer;


#define byteAtual (ponteiroBuffer+indiceBuffer)
//!< Ponteiro que aponta para o próximo byte do buffer ainda não usado
/*!< O buffer é uma reunião sequencial de bytes (array de bytes).
 * É necessário saber qual é o próximo byte não usado dentro do buffer.
 *O valor do próximo byte não usado pode ser calculado através da
 * seguinte fórmula: `LOCAL DO BYTE = INÍCIO DO BUFFER + 
 * BYTES JÁ USADOS`. O endereço da memória do início do buffer é indicado
 * pelo `ponteiroBuffer` enquanto o `indiceBuffer`marca quantos bytes já foram
 * usados. O resultado dessa soma é o endereço da memória do byte 
 * disponível para uso (e como isso é um endereço, deve ser usado como ponteiro). 
 * \see ponteiroBuffer, indiceBuffer, gravarBuffer(byte), enviar(byte *) */

 
 
#define delayResposta 25
//!< Valor em milisegundos de delay entre o envio de um byte e outro na comunicação
/*!< Esse valor é importante já que se esse valor fosse 0, vários bytes poderiam
 * ser enviados simultâneamente, levando à perda de dados (um 0110 seguido de 
 * um 1010 poderia acidentalmente se tornar um 1111 se os 0's forem atropelados).
 * O valor mínimo recomendado para esta variável é 5 milisegundos, porém este valor
 * pode variar dependendo da aplicação e dos dispositivos envolvidos. 
 * \see enviar(byte *) */
 
#define maxParametros 10
//!< Indica o valor máximo de parametros que um comando de comunicação pode ter
/*!< Esse valor é usado ao se intepretar uma mensagem, limitando o número de
 * parametros que um único comando pode ter. 
 * \see __processarTransmissao(void), tipoToken(byte *) */
 

//! Marca os tipos de tokens existentes: comando, 
//! valor, variável, marcador
/*! Essa enumeração indica que um token pode ser
 *		- um __comando__ (como `somar` ) ou 
 *		- um __valor__ (como `5`) ou 
 * 	- uma __variável__ (
 * como o `pino 5`) ou 
 * 	- um __marcador__ (como `Fim de 
 * Transmissão`)
 * 
 * Um *token* é o menor pedaço de informação
 * que compõem as mensagens trocadas com o servidor. */
 enum token {Desconhecido, Marcador, Comando, Valor, Variavel,  Modificador};

#endif
