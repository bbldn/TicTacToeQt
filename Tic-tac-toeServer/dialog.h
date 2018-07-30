#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QTcpServer>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTcpSocket>
#include <QMenuBar>
#include <QLabel>
#include <QTextEdit>
#include "showuserform.h"
#include "loggerwidget.h"
#include "myserver.h"
#include "strategy.h"

class Dialog : public QDialog{
    Q_OBJECT
    protected:
        QVBoxLayout* main;
        QMenuBar* bar;
        ShowUserForm* showUserFrm;
        LoggerWidget* logg;
        QPushButton* startS;
        QPushButton* stopS;
        MyServer* server;
        BDController* bd;
        void init();
    public:
        Dialog(QWidget *parent = 0);
        ~Dialog();
    public slots:
        void startServer();
        void stopServer();
        void showUsers();
};

#endif // DIALOG_H
