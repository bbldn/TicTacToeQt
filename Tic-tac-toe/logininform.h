#ifndef LOGININFORM_H
#define LOGININFORM_H

#include "myclient.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

class loginInForm : public QDialog{
    Q_OBJECT
    protected:
        QLineEdit* address;
        QLineEdit* port;
        QLineEdit* login;
        QLineEdit* password;
        MyClient* client;
        void init();
    public:
        explicit loginInForm(QDialog *parent = 0);
        MyClient* getMyClient();

    signals:

    public slots:
        void loginRigth(quint8 state);
        void errorConnect(QAbstractSocket::SocketError);
        void loginIN();
        void exi1t();
};

#endif // LOGININFORM_H
