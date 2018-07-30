#ifndef BDCONTROLLER_H
#define BDCONTROLLER_H

#include "QtSql/QSqlDatabase"

#include <QVector>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>

class BDController{
    protected:
        QSqlDatabase db;
    public:
        struct NameAndRecord{
            QString name;
            int record;
        };
        BDController();
        ~BDController();
        QString crypt(QString text);
        QString decrypt(QString text);
        void createTableUsers();
        void createTableRecords();
        void createTableLastParty();
        void addNewRecord(QString name);
        void addNewParty(QString field);
        bool isExistUser(QString name);
        bool LoginIN(QString name, QString password);
        void registerNewUser(QString name, QString password);
        void removeUser(QString name);
        void removeRecord(QString name);
        void changePassword(QString name, QString password);
        void cleanUsers();
        QVector<QString>* getAllFromUsers();
        QVector<NameAndRecord>* getAllFromRecords();
        QVector<QString>* getAllFromLastParty();
};

#endif // BDCONTROLLER_H
