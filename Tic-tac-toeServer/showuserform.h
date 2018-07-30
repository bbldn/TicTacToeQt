#ifndef SHOWUSERFORM_H
#define SHOWUSERFORM_H

#include <QDialog>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QMessageBox>

#include "adduserform.h"
#include "bdcontroller.h"
#include "changepasswordform.h"

class ShowUserForm : public QDialog{
    Q_OBJECT
    protected:
        int id;
        BDController* bd;
        QVector<QString>* vect;
        QTableWidget* table;
        addUserForm* addfrm;
        changePasswordForm* changeForm;
        void init();
        void initBD();
    public:
        explicit ShowUserForm(QWidget *parent = 0, BDController* bd = 0);
    signals:
    public slots:
        void add();
        void remove();
        void change();
        void cellClicked(int row, int column);
};

#endif // SHOWUSERFORM_H
