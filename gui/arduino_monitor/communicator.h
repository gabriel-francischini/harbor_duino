#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
#include <QtSerialPort/QSerialPortInfo>
#include <qserialport.h>
#include <QtCore>
//#include "communicator.moc"


class Communicator : public QObject{

public:
	Communicator();
	~Communicator();

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
	QString connectTo(QString name);
	bool hasPort();
	void setPort(QSerialPort *port);

private slots:
	void handleReadyRead();
	void handleError(QSerialPort::SerialPortError error);
	void handleTimeout();

private:

	Q_OBJECT

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
