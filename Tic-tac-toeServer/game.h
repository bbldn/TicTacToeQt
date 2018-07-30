#ifndef GAME_H
#define GAME_H

#include <QObject>

class Game: public QObject{
    Q_OBJECT
    public:
        explicit Game(QObject *parent = 0, QString crossLogin = "", QString circleLogin = "", int crossDes = -1, int circleDes = -1);
        static const int fieldSize = 3;
        void clean();
        int checkWin();//1 - cross, 2 - circle
        void MakeMove(QString login, int x, int y);
        void setFieldFromString(QString field);
        QString getCrossLogin();
        QString getCircleLogin();
        QString getFieldString();
        int getCrossDescriptor();
        int getCircleDescriptor();
        int getOpponentDescriptor(int des);
        int getOpponentDescriptor(QString login);
        QString getOpponentLogin(int des);
        QString getOpponentLogin(QString login);
    protected:
        int field[fieldSize][fieldSize];
        int crossDes;
        int circleDes;
        QString crossLogin;
        QString circleLogin;
        void init();
    signals:
        void Win(Game* game, QString login, int des);
        void Loss(Game* game, QString login, int des);
        void Draw(Game* game, QString crossLogin, QString circleLogin);//No one won
        void error(int e);
        /*1 - unknown login when trying make a move
         *2 - unknown coordinates when trying make a move
         *
         */
    public slots:
};

#endif // GAME_H
