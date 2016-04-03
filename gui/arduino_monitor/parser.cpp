#include "parser.h"
#include "QString"
#include "QtCore"

Parser::Parser(QObject *parent) : QObject(parent) {


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
	int words_taken = 0;
	QString result_word;
	QStringList result;
	result_word.append(user_input.first());
	bool is_not_first_run = false;

	foreach(QString input, user_copy){
		if(is_not_first_run){
			result_word.append(' ');
			result_word.append(input);
		}

		foreach(QString option, valid_options){
			if(result_word.compare(option)==0){
				for(; words_taken>=0; words_taken--)
					user_copy.removeAt(words_taken);

				result.append(result_word);
				foreach(QString word, user_copy)
					result.append(word);
				return result;
			}
		}
		is_not_first_run = true;
	}

	result.append(result_word);
	return result;
}
