#include "changepasswordform.h"

void changePasswordForm::init(){
    QVBoxLayout* main = new QVBoxLayout;
    this->setLayout(main);
    QLabel* passwordT = new QLabel("Пароль:", this);
    password = new QLineEdit;
    QHBoxLayout* one = new QHBoxLayout;
    one->addWidget(passwordT);
    one->addWidget(password);
    QLabel* newPasswordT = new QLabel("Повторите пароль:", this);
    newPassword = new QLineEdit;
    QHBoxLayout* two = new QHBoxLayout;
    two->addWidget(newPasswordT);
    two->addWidget(newPassword);
    QPushButton* ok = new QPushButton("OK", this);
    QPushButton* cancel = new QPushButton("Отмена", this);
    connect(ok, SIGNAL(released()), this, SLOT(change()));
    connect(cancel, SIGNAL(released()), this, SLOT(exi1t()));
    QHBoxLayout* three = new QHBoxLayout;
    three->addWidget(ok);
    three->addWidget(cancel);
    main->addLayout(one);
    main->addLayout(two);
    main->addLayout(three);
    password->setMaxLength(20);
    password->setEchoMode(QLineEdit::Password);
    password->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    newPassword->setMaxLength(20);
    newPassword->setEchoMode(QLineEdit::Password);
    newPassword->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);

}

changePasswordForm::changePasswordForm(QWidget *parent): QDialog(parent){
    init();
}

QString changePasswordForm::getLastPassword(){ return lastPassword;}
void changePasswordForm::exi1t(){ this->reject(); }

void changePasswordForm::change(){
    QString lastPassword = password->text();
    QString tmp = newPassword->text();
    if(lastPassword.length() < 5){
        QMessageBox error;
        error.setText("Пароль слишком короткий!");
        error.exec();
        return;
    }
    if(lastPassword == tmp){
        password->clear();
        newPassword->clear();
        this->accept();
    }else{
        QMessageBox error;
        error.setText("Пароли не совпадают");
        error.exec();
    }
}


