#ifndef CONSOLE_H
#define CONSOLE_H
#include <QtWidgets>

// Essa é a classe do console, responsável
// por prover uma interface de linha de comando
// para algumas funcionalidade, além de permitir
// que o usuário insira comandos diretamente,
// sem precisar de interfaces gráficas

// Esta classe é baseada em um editor
// de texto nativo ao Qt, herdando ele
class Console : public QTextEdit{

	Q_OBJECT

public:

	// Construtor
	Console();

	// Canais de comunicação?
	void sendData(QString string);
	int readData();
};

#endif // CONSOLE_H
