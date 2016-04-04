#ifndef CONSOLE_H
#define CONSOLE_H

// Bibliotecas necessárias
#include <QtWidgets>
#include <QObject>
#include "communicator.h"

// Essa é a classe do console, responsável
// por prover uma interface de linha de comando
// para algumas funcionalidade, além de permitir
// que o usuário insira comandos diretamente,
// sem precisar de interfaces gráficas


// Classe que será usada nesta classe
class Communicator;

// Esta classe é baseada em um editor
// de texto nativo ao Qt, herdando (d)ele
class Console : public QTextEdit{

	// Esta "marcador" indica
	// para inserir nesta linha
	// vários codigos referentes
	// aos objetos QT
	Q_OBJECT

public:

	// Construtor da classe
	explicit Console(QWidget *parent = 0);
	~Console();

	// Mostra o cursor de inatividade
	void showAwaiting();

	// Funções relativas ao comunicador com o Arduino
	void setCommunicator(Communicator *communicator);
	Communicator *getCommunicator();
	bool isCommOnline();

public slots:
	void external_show(QString string);

private:

	void show(QString string);

	QStringList implemented_commands;

	void setUpCommands();

	// Caractere que mostra que o terminal está
	// aguardando comandos
	 QChar awaiting;

	 // Variável para guardar o comunicador
	 Communicator *communicator;

	// Função responsável por inicializar o console
	void setUp();

	// Responsável por processar as teclas digitadas
	void keyPressEvent(QKeyEvent *key);

	// Função responsável pela mensagem de boas-vindas
	void greetings();
};

#endif // CONSOLE_H
