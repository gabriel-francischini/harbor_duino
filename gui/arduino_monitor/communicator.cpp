#include "communicator.h"
#include <QTextStream>

Communicator::Communicator(){
	setUpKnowCommands();
	connected = false;
}


QString Communicator::execute(QString command){
	QString unknown = QString("Comando desconhecido.\n");
	QStringList commands = command.split(' ', QString::SkipEmptyParts);
	#define comm_at(M) known_comm.value(commands[M].insert(commands[M].length() + 1, QString("")))
	#define level(M) if(commands.length() > M);
	//return QString("%1").arg(known_comm.value(commands[0], 2));
		switch (comm_at(0)) {
			case 1:
				level (1)
				switch (comm_at(1)) {
					case 2:
						QStringList ports = getNamePorts();
						QString result("");
						foreach(const QString &name, ports)
							result.append(name);
						return result;
						break;
				}
				break;
			default:
				return unknown;
				break;
	}
		return unknown;
}

void Communicator::setUpKnowCommands(){
	known_comm.insert("mostrar", 1);
	known_comm.insert("show", 1);
	known_comm.insert("listar", 1);
	known_comm.insert("portas", 2);
}

QList<QSerialPortInfo> Communicator::getPortList(){
	QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
	return list;
}


QStringList Communicator::getNamePorts(){
	QStringList list;
	foreach(const QSerialPortInfo &port, getPortList()){
		list << port.description();
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
