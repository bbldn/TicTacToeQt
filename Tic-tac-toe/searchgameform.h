#ifndef SEARCHGAMEFORM_H
#define SEARCHGAMEFORM_H
#define widthP 300
#define heigthP 283

#include "myclient.h"
#include "waiterwidget.h"

#include <QPainter>
#include <QDialog>
#include <QTimer>
#include <QVBoxLayout>

class searchGameForm: public QDialog{
    Q_OBJECT
    protected:
        MyClient* client;
        QString lastOppenentName;
        quint8 lastState;
        void init();
    private:
        int ii;
    public:
        explicit searchGameForm(QDialog* parent = 0, MyClient* client = 0);
        int getLastState();
        QString getLastName();
        int exe1c();

    signals:

    public slots:
        void gameFound(quint8 figure, QString nameOpponent);
};

#endif // SEARCHGAMEFORM_H
