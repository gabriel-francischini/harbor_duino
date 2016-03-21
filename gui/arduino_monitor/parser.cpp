#include "parser.h"
#include "QString"
#include "QtCore"

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

QStringList Parser::removeNullChar(QStringList list){
	foreach(QString string, list)
		string = string.simplified();
	return list;
}

int Parser::getKey(QString command){
	int result = known_commands.value(command);
	return result;
}

void Parser::setUpKnowCommands(){}

QStringList Parser::takeArg(QStringList user_input,
							QStringList valid_options){

	QStringList user_copy = user_input;
	QString str;

	foreach(QString input, user_copy)
		foreach(QString option, valid_options)
			str.append(input).append(option);

	QStringList user;
	user.append(str);
	return user;
}
