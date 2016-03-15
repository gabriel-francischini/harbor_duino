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
	void show(QString string);

private:

	// Caractere que mostra que o terminal está
	// aguardando comandos
	const QChar awaiting = '>';

	// Função responsável por inicializar o console
	void setUp();

	// Responsável por processar as teclas digitadas
	void keyPressEvent(QKeyEvent *key);

	// Função responsável pela mensagem de boas-vindas
	void greetings();
};

#endif // CONSOLE_H
