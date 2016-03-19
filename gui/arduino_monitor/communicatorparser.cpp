#include "communicatorparser.h"

CommunicatorParser::CommunicatorParser(Communicator *communicator){
	this->communicator = communicator;
	setUpKnowCommands();

}


QString CommunicatorParser::execute(QString command){
	QString unknown = QString("Comando desconhecido.\n");
	QStringList commands = command.split(' ', QString::SkipEmptyParts);
	commands = addNullChar(commands);

	if(isWordAt(commands, 0, "mostrar") &&
	   isWordAt(commands, 1, "portas") ){
		QStringList ports = this->communicator->getNamePorts();
		QString list_of_ports("");
		foreach(const QString &name, ports)
			list_of_ports.append(name);
		return list_of_ports;
	}
	return unknown;
}


void CommunicatorParser::setUpKnowCommands(){
	known_commands.insert("mostrar", 1);
	known_commands.insert("show", 1);
	known_commands.insert("listar", 1);
	known_commands.insert("portas", 2);
}
