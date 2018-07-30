#ifndef SOCANDLOGIN_H
#define SOCANDLOGIN_H

#include <QString>
#include <QTcpSocket>

struct SocAndLogin{
    QString login;
    QTcpSocket* socket;
    bool operator==(const SocAndLogin& obj){
        return (login == obj.login && socket == obj.socket)? true: false;
    }
};

#endif // SOCANDLOGIN_H
