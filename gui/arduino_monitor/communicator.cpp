#include "communicator.h"

Communicator::Communicator(){
	connected = false;
}


QString Communicator::execute(QString command){
	return QString("Commando desconhecido.\n");
}
