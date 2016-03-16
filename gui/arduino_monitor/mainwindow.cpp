#include "mainwindow.h"
#include "console.h"

// Construtor da janela principal
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

	// Adiciona um título à janela principal
	setWindowTitle(tr("Monitor de Arduino"));

	// Cria o espaço para dispor
	// widgets ao usuário
	ui_area = new QWidget;
	// Cria a barra de menus
	createMenuBar();
	// Cria um console
	Console *console = new Console;
	Communicator *communicator = new Communicator;
	console->setCommunicator(communicator);
	// Cria um layout
	QVBoxLayout *mainLayout = new QVBoxLayout;


	// Adiciona widgets ao layout
	mainLayout->setMenuBar(menuBar);
	mainLayout->addWidget(console);

	// Define a ui_area como widget central
	// e aplica um layout a ela
	setCentralWidget(ui_area);
	ui_area->setLayout(mainLayout);
}

// Destrutor
MainWindow::~MainWindow() {

}

// Função para criar a barra de menus
void MainWindow::createMenuBar() {

	// Cria a barra de menu
	menuBar = new QMenuBar;
	// Cria o menu "Arquivo" e seus submenus
	fileMenu = new QMenu(tr("&Arquivo"),this);
	exit = fileMenu->addAction(tr("&Sair"));

	// Adiciona os menus à barra de menus
	menuBar->addMenu(fileMenu);

	// Adiciona uma ação caso seja clicado em "Sair"
	connect(exit, SIGNAL(triggered()), this, SLOT(close()));

}
