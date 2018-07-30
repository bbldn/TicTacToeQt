#include "dialog.h"

void Dialog::init(){
    this->setMaximumHeight(500);
    this->setMinimumHeight(500);
    this->setMaximumWidth(500);
    this->setMinimumWidth(500);
    main = new QVBoxLayout;
    this->setLayout(main);
    bar = new QMenuBar;
    main->setMenuBar(bar);
    QMenu* usersM = new QMenu("Пользователи");
    bar->addMenu(usersM);
    QAction* showAllUsers = new QAction("Посмотреть всех пользователей");
    usersM->addAction(showAllUsers);
    connect(showAllUsers, &QAction::triggered, this, &showUsers);
    startS = new QPushButton("Запустить сервер");
    stopS = new QPushButton("Остановить сервер");
    connect(startS, SIGNAL (released()), this, SLOT (startServer()));
    connect(stopS, SIGNAL (released()), this, SLOT (stopServer()));
    stopS->setEnabled(false);
    QHBoxLayout* hor = new QHBoxLayout;
    hor->addWidget(startS);
    hor->addWidget(stopS);
    main->addLayout(hor);
    logg = new LoggerWidget(this);
    logg->resize(500, 350);
    main->addWidget(logg);
    bd = new BDController;
    showUserFrm = new ShowUserForm(this, bd);
    server = new MyServer(this, logg, bd);
    server->setStrategy(new Strategy(this, bd, logg));
}

Dialog::Dialog(QWidget *parent): QDialog(parent){
    init();
}

Dialog::~Dialog(){

}

void Dialog::startServer(){
    if(server->start()){
        startS->setEnabled(false);
        stopS->setEnabled(true);
    }
}

void Dialog::stopServer(){
    server->stop();
    startS->setEnabled(true);
    stopS->setEnabled(false);
}

void Dialog::showUsers(){
    showUserFrm->exec();
}
