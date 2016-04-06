#include "mainwindow.h"

// Janela principal e início do programa
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {


	// Adiciona um título à janela principal
	setWindowTitle(tr("Monitor de Arduino"));

	// Cria o espaço para dispor
	// widgets ao usuário
	ui_area = new QWidget(this);

	// Cria a barra de menus
	createMenuBar();

	// Cria o console
	// O console é basicamente o local principal
	// onde pode-se interagir diretamente com o programa,
	// sem recorrer à interface gráficas
	console = new Console(this);


	// Cria o comunicador
	// O Comunicador é basicamente a parte do programa responsável
	// por se comunicar com o harbor_duino nas suas mais variadas
	// formas
	communicator = new Communicator(this);
	console->setCommunicator(communicator);

	// Cria um layout
	QVBoxLayout *mainLayout = new QVBoxLayout(this);


	// Adiciona widgets ao layout
	mainLayout->setMenuBar(menuBar);
	mainLayout->addWidget(console);

	// Conecta os diferentes componentes do programa
	setSignalsAndSlots();

	// Define a ui_area como widget central
	// e aplica um layout a ela
	setCentralWidget(ui_area);
	ui_area->setLayout(mainLayout);
}

// Destrutor
MainWindow::~MainWindow() {}

// Função para criar a barra de menus
void MainWindow::createMenuBar() {

	// Cria a barra de menu
	// ela é "filha" da janela principal
	menuBar = new QMenuBar(this);

	// Cria o menu "Arquivo" e suas ações
	// o menu "arquivo" também é filho da janela principal
	fileMenu = new QMenu(tr("&Arquivo"),this);
	exit = fileMenu->addAction(tr("&Sair"));

	// Cria o menu "Opções" com suas ações
	// este menu também é hierarquicamente abaixo da
	// janela principal
	optionsMenu = new QMenu(tr("&Opções"), this);
	m_connect = optionsMenu->addAction(tr("&Conectar"));


	// Adiciona os menus à barra de menus
	menuBar->addMenu(fileMenu);
	menuBar->addMenu(optionsMenu);


}


// Função responsáveis por conectar os diferentes
// sinais e os diferentes slots.
// Quando um sinal é emito por alguma parte do programa,
// outras partes podem realizar alguma atividade (uma função "slot")
// baseando-se no tipo de sinal emitido e as informações
// contidas no sinal.
void MainWindow::setSignalsAndSlots(){

	// Adiciona uma ação caso seja clicado em "Sair"
	connect(exit, SIGNAL(triggered()), this, SLOT(close()));
	connect(m_connect, SIGNAL(triggered()), this, SLOT(connectTo()));


	// Dá ao comunicador uma forma de manusear o console
	connect(communicator, SIGNAL(portError(QString)),
			console, SLOT(external_show(QString)));
	// connect(communicator, SIGNAL(dataReceived(QString)),
	//		console, SLOT(external_show(QString)));
	connect(communicator, SIGNAL(portError(QString)),
			this, SLOT(connectTo(QString)));

}



// Essa é uma funcionalidade temporária
void MainWindow::connectTo(QString error){

	if(error == ""){
		if(QSerialPortInfo::availablePorts().isEmpty()){
			QMessageBox *diag = new QMessageBox(this);
			diag->setText("Não há portas disponíveis.");
			diag->exec();
		}

		else {
				QMessageBox *diag = new QMessageBox(this);
				QString message = communicator->connectTo(
								  (QSerialPortInfo::availablePorts()
								   .at(0)).portName());

				if(message == "") message = error;

				if(message.isEmpty() || message == "");
				else {
					diag->setText(message);
					diag->exec();
				}
		}
	}

	else {
		QMessageBox *diag = new QMessageBox(this);
		diag->setText(error);
		diag->exec();
	}

}
