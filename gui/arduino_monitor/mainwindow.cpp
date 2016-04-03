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
	Communicator *communicator;
	console->setCommunicator(communicator);

	//connected_port = new QSerialPort(this);
	//connected_port = new QSerialPort(this);
	//communicator->setPort(connected_port);

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

	optionsMenu = new QMenu(tr("&Opções"), this);
	m_connect = optionsMenu->addAction(tr("&Conectar"));
	menuBar->addMenu(optionsMenu);

	// Adiciona uma ação caso seja clicado em "Sair"
	connect(exit, SIGNAL(triggered()), this, SLOT(close()));
	connect(m_connect, SIGNAL(triggered()), this, SLOT(connectTo()));

}

void MainWindow::connectTo(){


	connected_port = new QSerialPort;
	if(QSerialPortInfo::availablePorts().isEmpty()){
		QMessageBox *diag = new QMessageBox;
		diag->setText("Não há portas disponíveis.");
		diag->exec();
	}

	else {
		connected_port->setPort(QSerialPortInfo::availablePorts().at(0));

		if(connected_port->open(QIODevice::ReadWrite)){
			QMessageBox *diag = new QMessageBox;
			diag->setText("Porta aberta com sucesso!");
			diag->exec();
			}
		else {
			QMessageBox *diag = new QMessageBox;
			diag->setText(QString("A porta não foi aberta. Erro %1: %2")
						  .arg(connected_port->error())
						  .arg(connected_port->errorString()));
			diag->exec();
		}
	}
}
