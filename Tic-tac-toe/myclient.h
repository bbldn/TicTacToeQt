#ifndef MYCLIENT_H
#define MYCLIENT_H

#include "mydatastream.h"
#include "nameandrecord.h"

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>

class MyClient: public QObject{
    Q_OBJECT
    protected:
        QTcpSocket* sok;
        QString address;
        quint16 port;
        void EventsInMatch(quint8 state);
        bool send(QByteArray block);
        void sendRecords(MyDataStream in);
        void checkRecords(MyDataStream in);
        void sendLastParty(MyDataStream in);
        void init();
    public:
        explicit MyClient(QObject *parent = 0);
        void loginIN(QString login, QString password);
        void searchGame();
        void endSearchGame();
        void sendMove(int x, int y);//Make a move
        bool connect(QString address, quint16 port);
        void getRecords();
        void getLastParty();
        void disconnect();
    signals:
        void loginin(quint8 state);
        void errorConnect(QAbstractSocket::SocketError a);
        void gameFound(quint8 figure, QString nameOpponent);
        void OpponentMadeMove(int x, int y);
        void onDisconnect();
        void OpponentOff();
        void Draw();//No
        void WeWon();
        void WeLost();
        void GettingRecordsFinished(QVector<NameAndRecord>* vect);
        void GettingLastPartyFinished(QVector<QString>* vect);
    public slots:
        void onSokReadyRead();
        void onSokDisconnected();
        void onSokError(QAbstractSocket::SocketError a);
};

#endif // MYCLIENT_H
