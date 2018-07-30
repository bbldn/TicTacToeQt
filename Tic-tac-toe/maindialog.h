#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "field.h"
#include "myclient.h"
#include "lastpartyform.h"
#include "searchgameform.h"
#include "showrecordsform.h"

#include <QDialog>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class MainDialog: public QDialog{
    Q_OBJECT
    protected:
        QLabel* state;
        QLabel* oName;
        QMenuBar* bar;
        QMenu* game;
        Field* field;
        QMenu* fieldM;
        QVBoxLayout* main;
        MyClient* client;
        searchGameForm* sForm;
        showRecordsForm* rForm;
        void outputStateGame(QString text);
        void init();
    public slots:
        void onDisconnect();
        void OpponentOff();
        void Draw();//No
        void WeWon();
        void WeLost();
        void searchAdversary();
        void showRecords();
        void showLastGame();
        void cleanField();
        void MadeMove(int x, int y);
        void OpponentMadeMove(int x, int y);
    public:
        MainDialog(QWidget *parent = 0, MyClient* client = 0);
        ~MainDialog();
};

#endif // MAINDIALOG_H
