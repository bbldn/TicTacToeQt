#include "adduserform.h"

#include <QMessageBox>

void addUserForm::init(){
    this->setWindowTitle("Добавление");
    QVBoxLayout* main = new QVBoxLayout;
    this->setLayout(main);
    QLabel* loginT = new QLabel("Логин:", this);
    login = new QLineEdit;
    QHBoxLayout* one = new QHBoxLayout;
    one->addWidget(loginT);
    one->addWidget(login);
    QLabel* passwordT = new QLabel("Пароль:", this);
    password = new QLineEdit;
    QHBoxLayout* two = new QHBoxLayout;
    two->addWidget(passwordT);
    two->addWidget(password);
    QPushButton* ok = new QPushButton("OK", this);
    QPushButton* cancel = new QPushButton("Отмена", this);
    connect(cancel, SIGNAL(released()), this, SLOT(exi1t()));
    connect(ok, SIGNAL(released()), this, SLOT(ad1d()));
    QHBoxLayout* three = new QHBoxLayout;
    three->addWidget(ok);
    three->addWidget(cancel);
    main->addLayout(one);
    main->addLayout(two);
    main->addLayout(three);
    login->setMaxLength(20);
    password->setMaxLength(20);
    password->setEchoMode(QLineEdit::Password);
    password->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
}

addUserForm::addUserForm(QWidget *parent): QDialog(parent){
    init();
}

QString addUserForm::getLastLogin(){ return lastLogin; }
QString addUserForm::getLastPassword(){ return lastPassword; }
void addUserForm::exi1t(){ this->reject(); }

void addUserForm::ad1d(){
    lastLogin = login->text();
    lastPassword = password->text();
    if(lastLogin.length() < 5){
        QMessageBox error;
        error.setText("Слишком короткий логин");
        error.exec();
        return;
    }
    if(lastPassword.length() < 5){
        QMessageBox error;
        error.setText("Слишком короткий пароль");
        error.exec();
        return;
    }
    login->clear();
    password->clear();
    this->accept();
}
