#include "bdcontroller.h"

BDController::BDController(){//Конструктор
    db = QSqlDatabase::addDatabase("QSQLITE");//Выбрать тип базы
    db.setDatabaseName("records.db");//Задаем имя файла базы
    db.open();//открытие базы
    createTableUsers();//создаем базу
    createTableRecords();
    createTableLastParty();
}

BDController::~BDController(){ db.close(); }

QString BDController::crypt(QString text){
    for(int i = 0; i < text.length(); i++){
        char c = text[i].toLatin1();
        c++;
        text[i] = c;
    }
    return text;
}

QString BDController::decrypt(QString text){
    for(int i = 0; i < text.length(); i++){
        char c = text[i].toLatin1();
        c--;
        text[i] = c;
    }
    return text;
}

void BDController::createTableUsers(){
    QSqlQuery query;
    query.exec("CREATE TABLE if not exists 'users' ('id' INTEGER PRIMARY KEY AUTOINCREMENT, 'name' text, 'password' text);");
}

void BDController::createTableRecords(){
    QSqlQuery query;
    query.exec("CREATE TABLE if not exists 'records' ('id' INTEGER PRIMARY KEY AUTOINCREMENT, 'name' text, 'wins' INTEGER);");
}

void BDController::createTableLastParty(){
    QSqlQuery query;
    query.exec("CREATE TABLE if not exists 'lastparty' ('id' INTEGER PRIMARY KEY AUTOINCREMENT, 'field' text);");
}

void BDController::addNewRecord(QString name){
    QSqlQuery query;
    query.exec(QString("SELECT wins FROM records WHERE name = '%1';").arg(name));
    while(query.next()){
        int tmp = query.value(0).toInt();
        tmp++;
        query.exec(QString("UPDATE records SET wins = %1 WHERE name = '%2';").arg(tmp).arg(name));
        return;
    }
    query.exec(QString("INSERT INTO records (name,wins) VALUES ('%1', '%2');").arg(name).arg(1));
}

void BDController::addNewParty(QString field){
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM lastparty;");
    int tmp = 0;
    while(query.next()){
        tmp = query.value(0).toInt();
        break;
    }
    query.exec(QString("INSERT INTO lastparty (field) VALUES ('%1');").arg(field));
    if(tmp > 3){
        query.exec("SELECT id FROM lastparty LIMIT 1;");
        while(query.next()){
            tmp = query.value(0).toInt();
            break;
        }
        query.exec(QString("DELETE FROM lastparty WHERE id = %1;").arg(tmp));
    }
}

bool BDController::isExistUser(QString name){
    QSqlQuery query;
    query.exec(QString("SELECT * FROM users WHERE name = '%1' ;").arg(name));
    while(query.next()){ return true; }
    return false;
}

void BDController::registerNewUser(QString name, QString password){
    QSqlQuery query;
    password = crypt(password);
    query.exec(QString("INSERT INTO users (name,password) VALUES ('%1', '%2');").arg(name).arg(password));
}

void BDController::removeUser(QString name){
    QSqlQuery query;
    query.exec(QString("DELETE FROM users WHERE name = '%1';").arg(name));
}

void BDController::removeRecord(QString name){
    QSqlQuery query;
    query.exec(QString("DELETE FROM records WHERE name = '%1';").arg(name));
}

bool BDController::LoginIN(QString name, QString password){//Вход
    QSqlQuery query;
    password = crypt(password);
    query.exec(QString("SELECT * FROM users WHERE name = '%1' AND password = '%2';").arg(name).arg(password));
    while(query.next()){ return true; }
    return false;
}

void BDController::cleanUsers(){
    QSqlQuery query;
    query.exec("DELETE FROM users");
}

void BDController::changePassword(QString name, QString password){
    QSqlQuery query;
    if(isExistUser(name)){
        password = crypt(password);
        query.exec(QString("UPDATE users SET password = '%1' WHERE name = '%2';").arg(password).arg(name));
    }
    qDebug(db.lastError().text().toStdString().c_str());
}

QVector<QString>* BDController::getAllFromUsers(){
    QVector<QString>* vect = new QVector<QString>;
    QSqlQuery query;
    query.exec("SELECT name FROM users;");
    while(query.next()){
        vect->push_back(query.value(0).toString());
    }
    return vect;
}

QVector<BDController::NameAndRecord> *BDController::getAllFromRecords(){
    QVector<NameAndRecord>* vect = new QVector<NameAndRecord>;
    QSqlQuery query;
    query.exec("SELECT name, wins FROM records;");
    while(query.next()){
        NameAndRecord tmp;
        tmp.name = query.value(0).toString();
        tmp.record = query.value(1).toInt();
        vect->push_back(tmp);
    }
    return vect;
}

QVector<QString> *BDController::getAllFromLastParty(){
    QVector<QString>* vect = new QVector<QString>;
    QSqlQuery query;
    query.exec("SELECT field FROM lastparty;");
    while(query.next()){
        vect->push_back(query.value(0).toString());
    }
    return vect;
}

