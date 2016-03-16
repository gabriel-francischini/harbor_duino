#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
#include <QtSerialPort/QSerialPortInfo>


class Communicator{

public:
	Communicator();
	bool isConnected();
	bool disconnect();
	QString execute(QString command);

private:
	bool connected;

};

#endif // COMMUNICATOR_H
