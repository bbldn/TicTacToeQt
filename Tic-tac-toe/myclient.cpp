#include "myclient.h"
#include <QDebug>

void MyClient::init(){
    sok = new QTcpSocket(this);
    QObject::connect(sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    QObject::connect(sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    QObject::connect(sok, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSokError(QAbstractSocket::SocketError)));
}

MyClient::MyClient(QObject *parent): QObject(parent){
    init();
}

void MyClient::loginIN(QString login, QString password){
    QByteArray block;
    MyDataStream out(&block, QIODevice::WriteOnly);
    out << (quint8)1 << login << password;
    send(block);
}

void MyClient::searchGame(){
    QByteArray block;
    MyDataStream out(&block, QIODevice::WriteOnly);
    out << (quint8)2 << (quint8)0;
    send(block);
}

void MyClient::endSearchGame(){
    QByteArray block;
    MyDataStream out(&block, QIODevice::WriteOnly);
    out << (quint8)2 << (quint8)1;
    send(block);
}

void MyClient::sendMove(int x, int y){
    if(x < 0 || y < 0) return;
    quint8 tmp = x * 10 + y;
    QByteArray block;
    MyDataStream out(&block, QIODevice::WriteOnly);
    out << (quint8)3 << tmp;
    send(block);
}

bool MyClient::connect(QString address, quint16 port){
    this->address = address;
    this->port = port;
    if(sok->isOpen()) return true;
    sok->connectToHost(address, port);
    return sok->waitForConnected();
}

void MyClient::getRecords(){
    QByteArray block;
    MyDataStream out(&block, QIODevice::WriteOnly);
    out << (quint8)5 << (quint8)0;
    send(block);
}

void MyClient::getLastParty(){
    QByteArray block;
    MyDataStream out(&block, QIODevice::WriteOnly);
    out << (quint8)5 << (quint8)1;
    send(block);
}

void MyClient::disconnect(){ sok->close(); }

void MyClient::onSokReadyRead(){
    QByteArray block;
    block = sok->readAll();
    MyDataStream in(&block, QIODevice::ReadOnly);
    if(in.isCorrect()){
        quint8 command;
        in >> command;
        switch (command) {
            case 1:{
                quint8 tmp;
                in >> tmp;
                emit loginin(tmp);
                break;
            }
            case 2:{
                quint8 tmp;
                QString name;
                in >> tmp;
                in >> name;
                emit gameFound(tmp, name);
            }
            case 3:{
                quint8 tmp;
                in >> tmp;
                int x = tmp / 10;
                int y = tmp - (x * 10);
                emit OpponentMadeMove(x, y);
                break;
            }
            case 4:{
                quint8 tmp;
                in >> tmp;
                EventsInMatch(tmp);
                break;
            }
            case 5:{
                checkRecords(in);
                break;
            }
            default:
                break;
        }
    }else{
        qDebug() << "Пришло: " << sok->bytesAvailable();
        qDebug() << "Было закодированно: " << in.lastLength();
    }
}

void MyClient::EventsInMatch(quint8 state){
    switch (state) {
        case 0:{
            emit OpponentOff();
            break;
        }
        case 1:{
            emit Draw();//No
            break;
        }
        case 2:{
            emit WeWon();
            break;
        }
        case 3:{
            emit WeLost();
            break;
        }
        default:
            break;
    }
}

bool MyClient::send(QByteArray block){
    sok->write(block);
    return sok->waitForBytesWritten();
}

void MyClient::sendRecords(MyDataStream in){
    quint16 length;
    in >> length;
    QVector<NameAndRecord>* vect = new QVector<NameAndRecord>();
    for(int i = 0; i < length; i++){
        NameAndRecord tmp;
        in >> tmp.name;
        in >> tmp.record;
        vect->push_back(tmp);
    }
    emit GettingRecordsFinished(vect);
}

void MyClient::checkRecords(MyDataStream in){
    quint8 tmp;
    in >> tmp;
    if(tmp == 0){
        sendRecords(in);
    }else{
        sendLastParty(in);
    }
}

void MyClient::sendLastParty(MyDataStream in){
    int length;
    in >> length;
    QVector<QString>* vect = new QVector<QString>();
    for(int i = 0; i < length; i++){
        QString tmp;
        in >> tmp;
        vect->push_back(tmp);
    }
    emit GettingLastPartyFinished(vect);
}

void MyClient::onSokDisconnected(){
    emit onDisconnect();
}

void MyClient::onSokError(QAbstractSocket::SocketError a){
    emit errorConnect(a);
}
