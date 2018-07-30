#ifndef LASTPARTYFORM_H
#define LASTPARTYFORM_H

#include "field.h"
#include "myclient.h"
#include "waiterwidget.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDialog>

class lastPartyForm: public QDialog{
    Q_OBJECT
    protected:
        QVBoxLayout* mainWidget;
        MyClient* client;
        WaiterWidget* waiterWidget;
        QTableWidget* table;
        QVector<QString>* vect;
        Field* field;
        void init();
    public:
        explicit lastPartyForm(QDialog *parent = 0, MyClient* client = 0, Field* field = 0);
        int exe1c();

    signals:

    public slots:
        void GettingLastPartyFinished(QVector<QString> *vect);
        void CellDoubleClicked(int x, int y);
};

#endif // LASTPARTYFORM_H
