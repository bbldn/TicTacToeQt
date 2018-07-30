#ifndef CHANGEPASSWORDFORM_H
#define CHANGEPASSWORDFORM_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class changePasswordForm: public QDialog{
    Q_OBJECT
    protected:
        QString lastPassword;
        QLineEdit* password;
        QLineEdit* newPassword;
        void init();
    public:
        explicit changePasswordForm(QWidget *parent = 0);
        QString getLastPassword();
    signals:

    public slots:
        void change();
        void exi1t();
};

#endif // CHANGEPASSWORDFORM_H
