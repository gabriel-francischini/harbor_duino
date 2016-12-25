#ifndef MAINWINDOW_H
#define MAINWINDOW_H


// Bibliotecas necessárias
#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include <QSerialPort>
#include "console.h"

// Classes que serão usadas e precisam ser
// declaradas previamente
QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class Console;
class Communicator;
QT_END_NAMESPACE


// Estrutura da janela principal
class MainWindow : public QMainWindow
{
	Q_OBJECT


public:

	// Construtor e destrutor, que são
	// responsáveis por iniciar e fechar
	// a tela inicial, respectivamente
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	enum ErrorOnConnection {Error, NoError};


private slots:
	void connectTo(QString error = 0, QSerialPortInfo port = QSerialPortInfo::availablePorts().first());
	void connectToBridge(QString portName);
	void generatePortList();

private:

	// Função para criar a barra de menus, no topo
	void createMenuBar();

	// Função por conectar os diferentes
	// componentes do programa
	void setSignalsAndSlots();


	// ui_area corresponde à area que o
	// programa pode dispor widgets para o usuário
	QWidget *ui_area;

	// menuBar é uma váriavel para guardar a
	// barra de menus, no topo
	QMenuBar *menuBar;

	// esses são os menus e submenus, além
	// das ações disponíveis a partir da
	// barra de menu
	QMenu *fileMenu;
	QMenu *optionsMenu;
	QMenu *m_connect;
	QAction *m_disconnect;
	QAction *exit;


	// Componentes não tão vísiveis, mas importantes,
	// da janela principal
	Console *console;
	Communicator *communicator;
	QSerialPortInfo *connected_port;


	QList<QAction> *portlist;
	QSignalMapper *signalMapper;
};

#endif // MAINWINDOW_H
