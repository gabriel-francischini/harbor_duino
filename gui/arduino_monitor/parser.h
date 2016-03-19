#ifndef PARSER_H
#define PARSER_H
#include <QtCore>

class Parser{

public:

	Parser();
	virtual QString execute(QString command);

protected:

	bool isWordAt(QStringList list, int position, QString word);
	int getKey(QString command);
	QStringList addNullChar(QStringList list);
	QMap<QString, int> known_commands;
	virtual void setUpKnowCommands();

};

#endif // PARSER_H
