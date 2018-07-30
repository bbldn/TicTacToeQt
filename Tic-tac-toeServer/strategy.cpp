#include "strategy.h"

Strategy::Strategy(QObject* parent, BDController* bd, LoggerWidget* logg): QObject(parent){
    this->bd = bd;
    this->logg = logg;
    init();
}
void Strategy::init(){}

int Strategy::searchUser(QString name){
    foreach(int i, users.keys()){
        if(users[i].login == name)
            return i;
    }
    return -2;
}

int Strategy::searchAt(int des){
    for(int i = 0; i < games.size(); i++){
        if(games[i]->getCrossDescriptor() == des
                || games[i]->getCircleDescriptor() == des)
            return i;
    }
    return -1;
}

void Strategy::finishGame(Game* game){
    logg->addText("Игра между "
                  + game->getCrossLogin() + " и "
                  + game->getCircleLogin()
                  + " закончена");
    disconnect(game, SIGNAL(Win(Game*, QString, int)), this, SLOT(Win(Game*, QString, int)));
    disconnect(game, SIGNAL(Draw(Game*, QString, QString)), this, SLOT(Draw(Game*, QString, QString)));
    games.removeAll(game);
}

void Strategy::cleanUsers(){ users.clear(); }

void Strategy::Win(Game* game, QString name, int des){
    QByteArray block;
    MyDataStream out(&block, QIODevice::WriteOnly);
    out << (quint8)4 << (quint8)2;
    send(users[des].socket, block);
    logg->addText("Игрок с ником: " + name + " выйграл");
    bd->addNewRecord(name);
    QByteArray bloc1k;
    MyDataStream ou1t(&bloc1k, QIODevice::WriteOnly);
    ou1t << (quint8)4 << (quint8)3;
    send(users[game->getOpponentDescriptor(des)].socket, bloc1k);
    logg->addText("Игрок с ником: " + game->getOpponentLogin(des) + " проиграл");
    bd->addNewParty(game->getFieldString());
    finishGame(game);
}

void Strategy::Draw(Game* game, QString crossName, QString circleName){
    QByteArray block;
    MyDataStream out(&block, QIODevice::WriteOnly);
    out << (quint8)4 << (quint8)1;
    send(users[game->getCrossDescriptor()].socket, block);
    send(users[game->getCircleDescriptor()].socket, block);
    logg->addText("Игра между "
                  + crossName + " и "
                  + circleName
                  + " завершилась ничьей");
    bd->addNewParty(game->getFieldString());
    finishGame(game);
}

bool Strategy::send(QTcpSocket* socket, QByteArray array){
    socket->write(array);
    return socket->waitForBytesWritten();
}

void Strategy::kill(int descriptor){
    int i = searchAt(descriptor);
    if(i >= 0){
        int des = games[i]->getOpponentDescriptor(descriptor);
        QByteArray block;
        MyDataStream out(&block, QIODevice::WriteOnly);
        out << (quint8)4 << (quint8)0;
        send(users[des].socket, block);
        finishGame(games[i]);
    }
    SocAndLogin tmp = users[descriptor];
    waitingGame.removeAll(tmp);
    users.remove(descriptor);
}

void Strategy::Go(QTcpSocket* socket, QByteArray array){
    MyDataStream in(&array, QIODevice::ReadOnly);
    if(in.isCorrect()){
        quint8 command;
        in >> command;
        switch (command) {
            case 1:{                
                loginin(in, socket);
                break;
            }
            case 2:{
                searchgame(in, socket);
                break;
            }
            case 3:{
                makeMove(in, socket);
                break;
            }
            case 5:{
                checkReComnd(in, socket);
                break;
            }
            default:
                logg->addText("Клиент с дескриптором " + QString::number(socket->socketDescriptor()) + " прислал неверную комманду");
                break;
        }
    }else{
        logg->addText("Клиент с дескриптором " + QString::number(socket->socketDescriptor()) + " прислал неверные/неполные данные");
    }
}

void Strategy::loginin(MyDataStream in, QTcpSocket* socket){
    QString login;
    QString password;
    in >> login;
    in >> password;
    QByteArray array;
    MyDataStream out(&array, QIODevice::WriteOnly);
    if(bd->LoginIN(login, password)){
        if(searchUser(login) == -2){
            SocAndLogin tmp;
            tmp.login = login;
            tmp.socket = socket;
            users[socket->socketDescriptor()] = tmp;
            out << (quint8)1 << (quint8)1;
            send(socket, array);
            logg->addText("Пользователь: " + login + " успешно вошел!");
        }else{
            out << (quint8)1 << (quint8)2;
            send(socket, array);
            logg->addText("Пользователь: " + login + " пытался зайти с двух ПК!");
        }

    }else{
        logg->addText("Пользователь: " + login + " не вошел!");
        out << (quint8)1 << (quint8)0;
        send(socket, array);
    }
}

void Strategy::searchgame(MyDataStream in, QTcpSocket* socket){
    quint8 tmp;
    in >> tmp;
    switch(tmp){
        case 0:{
            if(waitingGame.size() < 1){
                SocAndLogin tmp = users[socket->socketDescriptor()];
                waitingGame.push_back(tmp);
                logg->addText("Игрок с ником: "
                              + tmp.login
                              + " начал поиск соперника");
            }else{
                SocAndLogin tmp = waitingGame[0];
                Game* game = new Game(this, tmp.login, users[socket->socketDescriptor()].login, tmp.socket->socketDescriptor(), socket->socketDescriptor());
                games.push_back(game);
                connect(game, SIGNAL(Win(Game*, QString, int)), this, SLOT(Win(Game*, QString, int)));
                connect(game, SIGNAL(Draw(Game*, QString, QString)), this, SLOT(Draw(Game*, QString, QString)));
                waitingGame.removeAt(0);

                tmp = users[game->getCrossDescriptor()];
                SocAndLogin tm1p = users[game->getCircleDescriptor()];
                QByteArray bl1;
                MyDataStream st1(&bl1, QIODevice::WriteOnly);
                st1 << (quint8)2 << (quint8)1 << tm1p.login;
                send(tmp.socket, bl1);

                QByteArray bl2;
                MyDataStream st2(&bl2, QIODevice::WriteOnly);
                st2 << (quint8)2 << (quint8)2 << tmp.login;
                send(tm1p.socket, bl2);

                logg->addText("Игроки: "
                              + tmp.login
                              + " и "
                              + tm1p.login
                              + " начали играть");
            }
            break;
        }
        case 1:{
            SocAndLogin tmp = users[socket->socketDescriptor()];
            QString login = tmp.login;
            int ii = waitingGame.indexOf(tmp);
            if(ii >= 0){
                waitingGame.removeAt(ii);
                logg->addText("Игрок с ником: "
                              + login
                              + " закончил поиск соперника");
            }else{
                logg->addText("Игрок с ником: "
                              + login
                              + " пытался закончить игру"
                              + "хотя не начинал её поиск");
            }
            break;
        }
    }
}

void Strategy::makeMove(MyDataStream in, QTcpSocket* socket){
    quint8 tmp;
    in >> tmp;
    int x = tmp / 10;
    int y = tmp - (x * 10);
    if(x < 0 || x >= Game::fieldSize || y < 0 || y >= Game::fieldSize){
        logg->addText("Игрок с ником: "
                      + users[socket->socketDescriptor()].login
                      + " прислал неверные координаты");
        return;
    }
    int ii = searchAt(socket->socketDescriptor());
    if(ii < 0){
        qDebug() << "Игра отсутствует: " << socket->socketDescriptor();
        qDebug() << "Длинна массива с играми: " << games.size();
        return;
    }
    QString login = users[socket->socketDescriptor()].login;
    Game* game = games[ii];
    QByteArray bl1;
    MyDataStream st1(&bl1, QIODevice::WriteOnly);
    st1 << (quint8)3 << tmp;
    int des = game->getOpponentDescriptor(socket->socketDescriptor());
    send(users[des].socket, bl1);
    game->MakeMove(login, x, y);
    logg->addText("Игрок с ником: " + login
                  + " сделал ход по координатам "
                  + QString::number(x) + " "
                  + QString::number(y));
}

void Strategy::checkReComnd(MyDataStream in, QTcpSocket* socket){
    quint8 tmp;
    in >> tmp;
    if(tmp == 0){
        sendRecords(socket);
    }else{
        sendLastParty(socket);
    }
}

void Strategy::sendRecords(QTcpSocket* socket){
    logg->addText("Пользователь с именем: "
                  + users[socket->socketDescriptor()].login
                  + " решил получить рекорды");
    QVector<BDController::NameAndRecord>* vect = new QVector<BDController::NameAndRecord>();
    vect = bd->getAllFromRecords();
    quint16 length = vect->length();
    QByteArray block;
    MyDataStream out(&block, QIODevice::WriteOnly);
    out << (quint8)5 <<(quint8)0 << length;
    for(int i = 0; i < vect->length(); i++){
        BDController::NameAndRecord tmp;
        tmp = vect->takeAt(i);
        out << tmp.name << tmp.record;
    }
    send(socket, block);
}

void Strategy::sendLastParty(QTcpSocket *socket){
    logg->addText("Пользователь с именем: "
                  + users[socket->socketDescriptor()].login
                  + " решил получить последнии 3 партии");
    QVector<QString>* vect;
    vect = bd->getAllFromLastParty();
    QByteArray block;
    MyDataStream out(&block, QIODevice::WriteOnly);
    out << (quint8)5 << (quint8)1 << vect->length();
    for(int i = 0; i < vect->length(); i++)
        out << vect->takeAt(i);
    send(socket, block);
}

