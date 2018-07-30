#ifndef SHOWRECORDSFORM_H
#define SHOWRECORDSFORM_H

#include "myclient.h"
#include "waiterwidget.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>

class showRecordsForm: public QDialog{
    Q_OBJECT
    protected:
        MyClient* client;
        QVBoxLayout* main;
        WaiterWidget* ww;
        void init();
    public:
        explicit showRecordsForm(QDialog *parent = 0, MyClient* client = 0);
        int exe1c();
    signals:

    public slots:
        void okPress();
        void GettingRecordsFinished(QVector<NameAndRecord>* vect);
};

#endif // SHOWRECORDSFORM_H
