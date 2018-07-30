#ifndef ADDUSERFORM_H
#define ADDUSERFORM_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class addUserForm : public QDialog{
    Q_OBJECT
    protected:
        QLineEdit* password;
        QLineEdit* login;
        QString lastLogin;
        QString lastPassword;
        void init();
    public:
        explicit addUserForm(QWidget *parent = 0);
        QString getLastLogin();
        QString getLastPassword();
    signals:

    public slots:
        void exi1t();
        void ad1d();
};

#endif // ADDUSERFORM_H
