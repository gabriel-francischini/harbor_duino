#include "communicator.h"
#include <QTextStream>
#include "communicatorparser.h"
#include "mainwindow.h"

Communicator::Communicator(QObject *parent){
	setParent(parent);
	connected = false;
	this->connected_port = new QSerialPort(this);
	connect(connected_port, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
	connect(connected_port, SIGNAL(error(QSerialPort::SerialPortError)),
			this, SLOT(handleError(QSerialPort::SerialPortError)));
	connect(&timer, SIGNAL(timeout()), SLOT(handleTimeout()));
}

Communicator::~Communicator(){}

QString Communicator::execute(QString command){
	CommunicatorParser parser(this);
	return parser.execute(command);
}

void Communicator::handleReadyRead(){
	readArray.append(connected_port->readAll());

	QString data_string;

	foreach(char data, readArray){
	data_string.append(data);
	}

	data_string.append("");

	emit dataReceived(data_string);

	if(!timer.isActive())
		timer.start(10000);

	readArray.clear();
}


QString Communicator::handleError(QSerialPort::SerialPortError error){
	QString header = QString("Ocorreu um erro na porta %1."
							 "\nErro %2: ")
						.arg(connected_port->portName())
						.arg(connected_port->error());

	switch(error)
		case QSerialPort::NoError:{
		//	emit portError(QSerialPort::NoError);
		//	emit portError(QString("%1 Nenhum erro ocorreu (?).")
		//				   .arg(header));
			break;

		case QSerialPort::DeviceNotFoundError:
			emit portError(QSerialPort::DeviceNotFoundError);
			emit portError(QString("%1 O erro ocoreu ao tentar se"
								   " conectar a um dispositivo inexistente.")
						   .arg(header));
			break;
		case QSerialPort::PermissionError:
			emit portError(QSerialPort::PermissionError);
			emit portError(QString("%1 O erro ocorreu ao tentar se"
								   " conectar a uma porta já"
								   " conectada por outro"
								   " programa/processo ou o usuário não"
								   " tem permissões e credenciais suficientes"
								   " para conectar à porta.")
						   .arg(header));
			break;
		case QSerialPort::OpenError:
			emit portError(QSerialPort::OpenError);
			emit portError(QString("%1 O erro ocorreu ao tentar se"
								   " conectar a um dispositivo já conectado"
								   " neste programa.")
						   .arg(header));
			break;
		case QSerialPort::NotOpenError:
			emit portError(QSerialPort::NotOpenError);
			emit portError(QString("%1 O erro ocorreu ao tentar realizar"
								   " uma operação que só pode ser realizada"
								   " caso se esteja conectado a um dispos"
								   "itivo. Não há nenhum dispositivo cone"
								   "ctado.")
						   .arg(header));
			break;
		case QSerialPort::WriteError:
			emit portError(QSerialPort::WriteError);
			emit portError(QString("%1 Um erro de entrada/saída ocorreu"
								   " enquanto eram enviadas informações ao"
								   " dispositivo.")
						   .arg(header));
			break;
		case QSerialPort::ReadError:
			emit portError(QSerialPort::ReadError);
			emit portError(QString("%1 Um erro de entrada/saída ocorreu"
								   " enquanto eram lidos sinais do disposi"
								   "tivo.")
						   .arg(header));
			break;
		case QSerialPort::ResourceError:
			emit portError(QSerialPort::ResourceError);
			emit portError(QString("%1 Um erro de entrada/saída ocorreu"
								   " quando algum recurso se tornou in"
								   "disponível, por exemplo quando o dis"
								   "positivo é removido inesperadamente"
								   " do sistema.")
						   .arg(header));
			break;
		case QSerialPort::UnsupportedOperationError:
			emit portError(QSerialPort::UnsupportedOperationError);
			emit portError(QString("%1 Uma operação falhou pelo fato de"
								   " não ser suportada/permitida"
								   " pelo sistema operacional.")
						   .arg(header));
			break;
		case QSerialPort::TimeoutError:
			emit portError(QSerialPort::TimeoutError);
			emit portError(QString("%1 Um erro de tempo esgotado/timeout"
								   " ocorreu.")
						   .arg(header));
			break;
		case QSerialPort::UnknownError:
			emit portError(QSerialPort::UnknownError);
			emit portError(QString("%1 Um erro desconhecido ocorreu.")
						   .arg(header));
			break;

		default:
			emit portError(QString("%1 Um erro REALMENTE desconhecido"
								   " ocorreu.\n\t Corra para as colinas,"
								   " Lola, corra. Corra por sua vida.")
						   .arg(header));
			break;
	}

return QString();

}

void Communicator::handleTimeout(){

}

QList<QSerialPortInfo> Communicator::getPortList(){
	QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
	return list;
}


QStringList Communicator::getNamePorts(){
	QStringList list;
	foreach(const QSerialPortInfo &port, getPortList()){
		list << QString(port.portName());
	}
	return list;
}

QSerialPortInfo Communicator::getInfoPortByName(QString name){
	QSerialPortInfo port_info;
	foreach(const QSerialPortInfo &port, getPortList())
		if(port.portName() == name)
			port_info = port;
	return port_info;
}

QString Communicator::connectTo(QString name){


//	emit portError(QString("Essa é a vida. *cigarro*"));
//	this->connected_port = new QSerialPort;
	if(!isPortValid(name)) return QString("A porta \"%1\" é inválida.").arg(name);
	this->connected_port->setPort(getInfoPortByName(name));
	//this->connected_port->setPort(QSerialPortInfo::availablePorts().at(0));
	//connected_port->setPortName("COM7");
	//connected_port->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);
	//connected_port->setDataBits(QSerialPort::Data8);
	//connected_port->setParity(QSerialPort::NoParity);
	//connected_port->setStopBits(QSerialPort::OneStop);
	//connected_port->setFlowControl(QSerialPort::NoFlowControl);
	if(this->connected_port->open(QIODevice::ReadWrite)){
		beConnected();
		QString message =QString("Conectado à porta %1, na velocidade de "
						  "%2 bytes por segundo, com %3 bits de informação.")
					   .arg(connected_port->portName()).arg(connected_port->
						baudRate()).arg(connected_port->dataBits());
		return message;
		}

	else return QString("");

	return QString("Comportamento inesperado.");
}

void Communicator::beConnected(){
	connected = true;
}


bool Communicator::isPortValid(QString name){

	foreach(const QSerialPortInfo &port, getPortList())
		if(port.portName() == name) return true;

	return false;
}


QString Communicator::getPortDesc(QString portname){
	return getInfoPortByName(portname).description();
}

QString Communicator::getPortLocation(QString name){
	return getInfoPortByName(name).description();
}

QString Communicator::getPortManufacturer(QString name){
	return getInfoPortByName(name).manufacturer();
}

QString Communicator::getProduct(QString name){
	if(getInfoPortByName(name).hasProductIdentifier())
		return QString("%1").arg(getInfoPortByName(name)
								 .productIdentifier());
	else
		return QString("N/A");
}

QString Communicator::getSerialNumber(QString name){
	return getInfoPortByName(name).serialNumber();
}

QString Communicator::getVendor(QString name){
	if(getInfoPortByName(name).hasVendorIdentifier())
		return QString("%1").arg(getInfoPortByName(name)
					 .vendorIdentifier());
	else
		return QString("N/A");
}

bool Communicator::isBusy(QString name){
	return getInfoPortByName(name).isBusy();
}

bool Communicator::isConnected(){
	return connected;
}

bool Communicator::hasPort(){

	return isPortAvailable;
}

void Communicator::setPort(QSerialPort *port){
	this->connected_port = port;
	isPortAvailable = true;
}
