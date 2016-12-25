#ifndef COMMUNICATORPARSER_H
#define COMMUNICATORPARSER_H
#include "communicator.h"
#include "parser.h"

class Communicator;

class CommunicatorParser : public Parser{
public:
	CommunicatorParser(Communicator *communicator, QObject *parent = 0);
	QString execute(QString command);
private:
	Communicator *communicator;
	void setUpKnowCommands();
};

#endif // COMMUNICATORPARSER_H
