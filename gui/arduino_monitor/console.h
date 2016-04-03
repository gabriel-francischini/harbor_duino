#ifndef CONSOLE_H
#define CONSOLE_H
#include <QtWidgets>
#include <QObject>
#include "communicator.h"

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
	explicit Console(QWidget *parent = 0);
	~Console();

	// Canais de comunicação
	void show(QString string);
	void showAwaiting();

	// Funções relativas ao comunicador com o Arduino
	void setCommunicator(Communicator *communicator);
	Communicator *getCommunicator();
	bool isCommOnline();
	void unsetCommunicator();

private:

	QStringList implemented_commands;

	void setUpCommands();

	// Caractere que mostra que o terminal está
	// aguardando comandos
	 QChar awaiting;

	 // Variáveis para guardar o comunicador
	 // e se ele já está online
	 bool comm_online;
	 Communicator *communicator;

	// Função responsável por inicializar o console
	void setUp();

	// Responsável por processar as teclas digitadas
	void keyPressEvent(QKeyEvent *key);

	// Função responsável pela mensagem de boas-vindas
	void greetings();
};

#endif // CONSOLE_H
