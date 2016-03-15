#ifndef CONSOLE_H
#define CONSOLE_H
#include <QtWidgets>

class Console : public QTextEdit{

    Q_OBJECT

public:

    Console();
    void sendData(QString string);
    int readData();
};

#endif // CONSOLE_H
