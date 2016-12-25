#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	// Cria o programa
	QApplication application(argc, argv);

	// Cria a janela pricipal
	MainWindow mainwindow;

	// Deixa a janela principal visível
	mainwindow.show();

	// Fecha o programa e retorna ao sistema operacional
	// quando a janela principal fechar
	return application.exec();
}
