#include "myserver.h"
#include <QDebug>

void MyServer::init(){
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newClient()));
    connect(tcpServer, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(acceptError(QAbstractSocket::SocketError)));
}

MyServer::MyServer(QObject* parent, LoggerWidget *logg, BDController* bd): QObject(parent){
    this->logg = logg;
    this->bd = bd;
    init();
}

void MyServer::setStrategy(Strategy* strategy){ command = strategy; }

bool MyServer::start(){
    bool tmp = tcpServer->listen(QHostAddress::Any, PORT);
    if(!tmp){
        logg->addText("Ошибка запуска сервера: " + tcpServer->errorString());
        return false;
    }
    logg->addText("Сервер запущен");
    return true;
}

void MyServer::stop(){
    foreach(int key, clients.keys()){
        QTextStream os(clients[key]);
        os.setAutoDetectUnicode(true);
        os << QDateTime::currentDateTime().toString() << "\n";
        clients[key]->close();
        clients.remove(key);
    }
    tcpServer->close();
    command->cleanUsers();
    logg->addText("Сервер остановлен");
}

void MyServer::newClient(){
    QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
    int id = clientSocket->socketDescriptor();
    clients[id] = clientSocket;
    logg->addText("Новый клиент с дескриптором:" + QString::number(id));
    connect(clients[id], SIGNAL(disconnected()), this, SLOT(clientOff()));
    connect(clients[id], SIGNAL(readyRead()), this, SLOT(readyReady()));
}

void MyServer::clientOff(){
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    disconnect(clientSocket, SIGNAL(disconnected()), this, SLOT(clientOff()));
    disconnect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyReady()));
    int tmp;
    foreach(int key, clients.keys()){
        if(clients[key] == clientSocket){
            clients.remove(key);
            command->kill(key);
            tmp = key;
            break;
        }
    }
    logg->addText("Клиент с дескриптором: " +
                  QString::number(tmp)
                  + " отсоединился");
}

void MyServer::readyReady(){
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    command->Go(clientSocket, clientSocket->readAll());
}

void MyServer::acceptError(QAbstractSocket::SocketError error){
    qDebug() << "Ошибка на сервере: " << error;
}
