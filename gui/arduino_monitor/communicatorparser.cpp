#include "communicatorparser.h"

CommunicatorParser::CommunicatorParser(Communicator *communicator,
									   QObject *parent){
	setParent(parent);
	this->communicator = communicator;
	setUpKnowCommands();

}


QString CommunicatorParser::execute(QString command){
	QString unknown = QString("Comando desconhecido.\n");
	QStringList commands = command.split(' ', QString::SkipEmptyParts);
	commands = addNullChar(commands);

	if(commands.size() > 1){
		if(isWordAt(commands, 0, "mostrar") &&
			isWordAt(commands, 1, "portas") ){
			QStringList ports = this->communicator->getNamePorts();
			QString list_of_ports("");
			foreach(const QString &name, ports)
				list_of_ports.append(name);
			return list_of_ports;
		}

		if(isWordAt(commands, 0, "enviar")){
			int base = 10;
			if(isWordAt(commands, 1, "bin")){
				base = 2;
			}
			else if(isWordAt(commands, 1, "oct")){
				base = 8;
			}
			else if(isWordAt(commands, 1, "dec")){
			}
			else if(isWordAt(commands, 1, "hex")){
				base = 16;
			}

			bool test = true;

			QStringList data = commands;
			data.removeFirst();
			data.removeFirst();
			foreach (QString string, data) {
				bool ok;
				string.toInt(&ok, base);
				test = test && ok;
			}
			if(test){
				foreach(QString string, data){
					int value = string.toInt(&test, base);
					communicator->write((byte) value);
				}
				return QString("");
			}
		}

	}

	if(commands.size() > 2){
		if(isWordAt(commands, 0, "conectar") &&
				isWordAt(commands, 1, "porta")){
				commands.removeFirst();
				commands.removeFirst();

				commands = takeArg(commands, this->communicator->getNamePorts());
				removeNullChar(commands);
				return this->communicator->connectTo(commands.first());
		}
	}
	return unknown;
}


void CommunicatorParser::setUpKnowCommands(){
	known_commands.insert("mostrar", 1);
	known_commands.insert("show", 1);
	known_commands.insert("listar", 1);
	known_commands.insert("portas", 2);
	known_commands.insert("porta", 2);
	known_commands.insert("conectar", 3);
	known_commands.insert("base", 4);
	known_commands.insert("bin", 5);
	known_commands.insert("2", 5);
	known_commands.insert("oct", 6);
	known_commands.insert("8", 6);
	known_commands.insert("dec", 7);
	known_commands.insert("10", 7);
	known_commands.insert("hex", 8);
	known_commands.insert("16", 8);
	known_commands.insert("enviar", 9);
	known_commands.insert("env", 9);
}
