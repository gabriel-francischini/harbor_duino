#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H


// Bibliotecas necessárias
#include <QtSerialPort/QSerialPortInfo>
#include <qserialport.h>
#include <QtCore>
#include "mainwindow.h"



// Esse é o comunicador, responsável
// pela interação direta com o harbor_duino
class Communicator : public QObject{

	Q_OBJECT

public:
	explicit Communicator(QObject *parent = 0);
	~Communicator();

	bool isConnected();

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
	QString connectTo(QString name);
	bool hasPort();
	void setPort(QSerialPort *port);

	enum n_base {BIN, OCT, DEC, HEX};

signals:
	void portError(QString error);
	void portError(QSerialPort::SerialPortError error);
	void dataReceived(QString data);
	void disconnected();

public slots:
	bool disconnect();
	void write(byte data);


private slots:
	void handleReadyRead();
	QString handleError(QSerialPort::SerialPortError error);
	void handleTimeout();

private:

	QByteArray readArray;
	QByteArray writeArray;
	QTimer timer;
	qint64 bytesWritten;
	int MaxTimeout;
	void beConnected();
	QSerialPort *connected_port;
	bool connected;
	QList<QSerialPortInfo> getPortList();
	bool isPortAvailable;

};

#endif // COMMUNICATOR_H
