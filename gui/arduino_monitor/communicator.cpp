#include "communicator.h"
#include <QTextStream>
#include "communicatorparser.h"

Communicator::Communicator(){
	connected = false;
	connect(connected_port, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
	connect(connected_port, SIGNAL(error(QSerialPort::SerialPortError)),
			this, SLOT(handleError(QSerialPort::SerialPortError)));
	connect(&timer, SIGNAL(timeout()), SLOT(handleTimeout()));
}


QString Communicator::execute(QString command){
	CommunicatorParser parser(this);
	return parser.execute(command);
}

void Communicator::handleReadyRead(){
	readArray.append(connected_port->readAll());

	if(!timer.isActive())
		timer.start(10000);
}

void Communicator::handleError(QSerialPort::SerialPortError){

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

	//connected_port = new QSerialPort;
	//if(!isPortValid(name)) return QString("A porta \"%1\" é inválida.").arg(name);
	//connected_port->setPort(getInfoPortByName(name));
	connected_port->setPort(QSerialPortInfo::availablePorts().at(0));
	//connected_port->setPortName("COM7");
	//connected_port->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);
	//connected_port->setDataBits(QSerialPort::Data8);
	//connected_port->setParity(QSerialPort::NoParity);
	//connected_port->setStopBits(QSerialPort::OneStop);
	//connected_port->setFlowControl(QSerialPort::NoFlowControl);
	if(connected_port->open(QIODevice::ReadWrite)){
		//beConnected();
		//return QString(QString("Conectado à porta %1, na velocidade de "
		//				  "%2 bytes por segundo, com %3 bits de informação.")
		//			   .arg(connected_port->portName()).arg(connected_port->
		//				baudRate()).arg(connected_port->dataBits()));
		}
	//else return QString("Erro ao tentar abrir a porta %1.")
	//		.arg(connected_port->portName());

	return QString("Comando desativado por questões técnicas."
				   "Utilize a interface gráfica para esta função.");
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
	connected_port = port;
	isPortAvailable = true;
}
