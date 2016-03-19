#include "parser.h"

Parser::Parser(){


}


QString Parser::execute(QString command){
	return command.append("Erro: classe abstrata.");
}

bool Parser::isWordAt(QStringList list, int position, QString word){
	return getKey(list.at(position)) == known_commands.value(word);
}

QStringList Parser::addNullChar(QStringList list){
	foreach(QString string, list)
		string.insert(string.length() + 1, QString(""));
	return list;
}

int Parser::getKey(QString command){
	int result = known_commands.value(command);
	return result;
}

void Parser::setUpKnowCommands(){}
