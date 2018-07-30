#ifndef COMMANDER_H
#define COMMANDER_H

#include "bdcontroller.h"
#include "descriptors.h"
#include "game.h"
#include "loggerwidget.h"
#include "mydatastream.h"
#include "socandlogin.h"

#include <QList>
#include <QObject>
#include <QTcpSocket>

class Strategy: public QObject{
    Q_OBJECT
    protected:
        QMap<int, SocAndLogin> users;
        QList<SocAndLogin> waitingGame;
        QList<Game*> games;
        LoggerWidget* logg;
        BDController* bd;
        void init();
        int searchUser(QString name);
        int searchAt(int des);
        void finishGame(Game* game);
        bool send(QTcpSocket* socket, QByteArray array);
        void loginin(MyDataStream in, QTcpSocket* socket);
        void searchgame(MyDataStream in, QTcpSocket* socket);
        void makeMove(MyDataStream in, QTcpSocket* socket);
        void checkReComnd(MyDataStream in, QTcpSocket* socket);
        void sendRecords(QTcpSocket* socket);
        void sendLastParty(QTcpSocket* socket);
    public:
        explicit Strategy(QObject* parent = 0,
                           BDController* bd = 0,
                           LoggerWidget *logg = 0);
        void Go(QTcpSocket *socket, QByteArray array);
        void kill(int descriptor);
        void cleanUsers();

    signals:

    public slots:
        void Win(Game* game, QString name, int des);
        void Draw(Game* game, QString crossName, QString circleName);
};

#endif // COMMANDER_H
