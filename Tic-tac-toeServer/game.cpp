#include "game.h"
#include <QDebug>
void Game::init(){
    clean();
}

Game::Game(QObject *parent, QString crossLogin, QString circleLogin, int crossDes, int circleDes): QObject(parent){
    this->crossLogin = crossLogin;
    this->circleLogin = circleLogin;
    this->circleDes = circleDes;
    this->crossDes = crossDes;
    init();
}

void Game::clean(){
    for(int i = 0; i < fieldSize; i++)
        for(int j = 0; j < fieldSize; j++)
            field[i][j] = 0;
}

int Game::checkWin(){
    /*rows*/
    if(field[0][2] == field[0][1] && field[0][1]  == field[0][0] && field[0][0] != 0)
       return field[0][0];
    if(field[1][2] == field[1][1] && field[1][1]  == field[1][0] && field[1][0] != 0)
       return field[1][0];
    if(field[2][2] == field[2][1] && field[2][1]  == field[2][0] && field[2][0] != 0)
       return field[2][0];
    /*columns*/
    if(field[2][0] == field[1][0] && field[1][0]  == field[0][0] && field[0][0] != 0)
       return field[0][0];
    if(field[2][1] == field[1][1] && field[1][1]  == field[0][1] && field[0][1] != 0)
       return field[0][1];
    if(field[2][2] == field[1][2] && field[1][2]  == field[0][2] && field[0][2] != 0)
       return field[0][2];
    /*diagonals*/
    if(field[2][2] == field[1][1] && field[1][1]  == field[0][0] && field[0][0] != 0)
       return field[0][0];
    if(field[2][0] == field[1][1] && field[1][1]  == field[0][2] && field[0][2] != 0)
       return field[0][2];
    /*Draw*/
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(field[i][j] == 0) return 0;
    return -1;
}

void Game::MakeMove(QString login, int x, int y){
    if(x >= fieldSize || x < 0 || y >= fieldSize || y < 0){
        emit error(2);
        return;
    }
    if(login == crossLogin){
        field[x][y] = 1;
    }else if(login == circleLogin){
        field[x][y] = 2;
    }else{
        emit error(1);
        return;
    }
    int tmp = checkWin();
    switch (tmp) {
        case 1:{
            emit Win(this, crossLogin, crossDes);
            emit Loss(this, circleLogin, circleDes);
            break;
        }
        case 2:{
            emit Win(this, circleLogin, circleDes);
            emit Loss(this, crossLogin, crossDes);
            break;
        }
        case -1:{
            emit Draw(this, crossLogin, circleLogin);
            break;
        }
        default:
            break;
    }
}

void Game::setFieldFromString(QString field){
    QStringList tmp = field.split(',');
    if(tmp.length() < 9 || tmp.length() > 9) return;
    for(int i = 0, l = 0; i < fieldSize; i++){
        for(int j = 0; j < fieldSize; j++, l++){
            this->field[i][j] = atoi(tmp[l].toStdString().c_str());
        }
    }
}

QString Game::getCrossLogin(){ return crossLogin; }
QString Game::getCircleLogin(){ return circleLogin; }

QString Game::getFieldString(){
    QString tmp;
    for(int i = 0; i < fieldSize; i++){
        for(int j = 0; j < fieldSize; j++){
            tmp += QString::number(field[i][j]) + ",";
        }
    }
    tmp.remove(tmp.length() - 1, 1);
    return tmp;
}
int Game::getCrossDescriptor(){ return crossDes; }
int Game::getCircleDescriptor(){ return circleDes;}
int Game::getOpponentDescriptor(int des){ return (crossDes == des)? circleDes: crossDes; }
int Game::getOpponentDescriptor(QString login){ return (crossLogin == login)? circleDes: crossDes; }
QString Game::getOpponentLogin(int des){ return (crossDes == des)? circleLogin: crossLogin; }
QString Game::getOpponentLogin(QString login){ return (crossLogin == login)? circleLogin: crossLogin; }
