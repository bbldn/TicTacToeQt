#ifndef MYSERVER_H
#define MYSERVER_H
#define PORT 9996

#include "loggerwidget.h"
#include "strategy.h"
#include "bdcontroller.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class MyServer: public QObject{
    Q_OBJECT
    protected:
        QTcpServer* tcpServer;
        QMap<int, QTcpSocket* > clients;
        LoggerWidget* logg;
        Strategy* command;
        BDController* bd;
        void init();
    public:
        explicit MyServer(QObject *parent = 0, LoggerWidget* logg = 0, BDController* bd = 0);
        void setStrategy(Strategy* strategy);
        bool start();
        void stop();
    public slots:
        void newClient();
        void clientOff();
        void readyReady();
        void acceptError(QAbstractSocket::SocketError error);
};

#endif // MYSERVER_H
