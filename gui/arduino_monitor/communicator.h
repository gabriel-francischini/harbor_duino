#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
#include <QtSerialPort/QSerialPortInfo>
#include <QtCore>


class Communicator{

public:
	Communicator();
	bool isConnected();
	bool disconnect();
	QString execute(QString command);

	QStringList getNamePorts();
	QSerialPortInfo getInfoPortByName(QString name);
	bool isPortValid(QString name);
	QString getPortDesc(QString name);
	QString getPortLocation(QString name);
	QString getPortManufacturer(QString name);
	QString getSerialNumber(QString name);
	QString getVendor(QString name);
	QString getProduct(QString name);
	bool isBusy(QString name);

private:

	int testCommand(QStringList *command);
	QSerialPort *connected_port;
	QStringList addNullChar(QStringList list);
	bool connected;
	QList<QSerialPortInfo> getPortList();
	QMap<QString, int> known_comm;
	void setUpKnowCommands();

};

#endif // COMMUNICATOR_H
