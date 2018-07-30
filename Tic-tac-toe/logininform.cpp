#include "logininform.h"

void loginInForm::init(){
    QVBoxLayout* main = new QVBoxLayout;
    this->setLayout(main);
    QHBoxLayout* one = new QHBoxLayout;
    QLabel* addressL = new QLabel("Адрес: ");
    address = new QLineEdit;
    one->addWidget(addressL);
    one->addWidget(address);
    main->addLayout(one);
    QHBoxLayout* two = new QHBoxLayout;
    QLabel* portL = new QLabel("Порт: ");
    port = new QLineEdit(this);
    two->addWidget(portL);
    two->addWidget(port);
    main->addLayout(two);
    QHBoxLayout* three = new QHBoxLayout;
    QLabel* loginL = new QLabel("Логин: ");
    login = new QLineEdit(this);
    login->setMaxLength(20);
    three->addWidget(loginL);
    three->addWidget(login);
    main->addLayout(three);
    QHBoxLayout* four = new QHBoxLayout;
    QLabel* passwordL = new QLabel("Пароль: ");
    password = new QLineEdit;
    password->setMaxLength(20);
    password->setEchoMode(QLineEdit::Password);
    password->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    four->addWidget(passwordL);
    four->addWidget(password);
    main->addLayout(four);
    QHBoxLayout* five = new QHBoxLayout;
    QPushButton* loginIN = new QPushButton("Войти");
    QPushButton* cancel = new QPushButton("Отмена");
    five->addWidget(loginIN);
    five->addWidget(cancel);
    connect(loginIN, SIGNAL(released()), this, SLOT(loginIN()));
    connect(cancel, SIGNAL(released()), this, SLOT(exi1t()));
    main->addLayout(five);
    client = new MyClient(this);
    connect(client, SIGNAL(loginin(quint8)), this, SLOT(loginRigth(quint8)));
    connect(client, SIGNAL(errorConnect(QAbstractSocket::SocketError)), this, SLOT(errorConnect(QAbstractSocket::SocketError)));
}

loginInForm::loginInForm(QDialog *parent): QDialog(parent){
    init();
}

MyClient *loginInForm::getMyClient(){ return client; }

void loginInForm::loginRigth(quint8 state){
    switch(state){
        case 1:{
            this->accept();
            return;
            break;
        }
        case 2:{
            QMessageBox error;
            error.setText("Пользователь с таким именем уже зашел");
            error.exec();
            break;
        }
        default:{
            QMessageBox error;
            error.setText("Неверный логин/Пароль");
            error.exec();
            break;
        }
    }
}

void loginInForm::errorConnect(QAbstractSocket::SocketError){
    client->disconnect();
}

void loginInForm::loginIN(){
    QMessageBox error;
    if(address->text().length() < 5){
        error.setText("Слишком короткий адрес!");
        error.exec();
        return;
    }
    if(port->text().length() < 1){
        error.setText("Слишком короткий порт!");
        error.exec();
        return;
    }
    if(login->text().length() < 5){
        error.setText("Слишком короткий логин!");
        error.exec();
        return;
    }
    if(password->text().length() < 5){
        error.setText("Слишком короткий пароль!");
        error.exec();
        return;
    }
    if(!client->connect(address->text(), port->text().toInt())){
        QMessageBox error;
        error.setText("Проблемы с подключением к серверу!");
        error.exec();
        return;
    }
    client->loginIN(login->text(), password->text());
}

void loginInForm::exi1t(){
    client->disconnect();
    this->reject();
}
