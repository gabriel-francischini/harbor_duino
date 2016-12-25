#ifndef PARSER_H
#define PARSER_H
#include <QtCore>

class Parser : public QObject{

	Q_OBJECT


public:

	Parser(QObject *parent = 0);
	virtual QString execute(QString command);

protected:

	bool isWordAt(QStringList list, int position, QString word);
	int getKey(QString command);
	QStringList addNullChar(QStringList list);
	QMap<QString, int> known_commands;
	virtual void setUpKnowCommands();
	virtual QStringList takeArg(QStringList user_input, QStringList valid_options);
	QStringList removeNullChar(QStringList list);

};

#endif // PARSER_H
