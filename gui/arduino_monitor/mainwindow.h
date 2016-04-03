#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include <QSerialPort>

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


private slots:
	void connectTo();

private:

	// Função para criar a barra de menus, no topo
	void createMenuBar();


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
	QAction *m_connect;
	QAction *exit;
	QSerialPort *connected_port;

};

#endif // MAINWINDOW_H
