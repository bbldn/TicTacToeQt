#include "searchgameform.h"

searchGameForm::searchGameForm(QDialog* parent, MyClient *client): QDialog(parent){
    this->client = client;
    init();
}

int searchGameForm::getLastState(){ return lastState; }
QString searchGameForm::getLastName(){ return lastOppenentName; }

void searchGameForm::gameFound(quint8 figure, QString nameOpponent){
    lastState = figure;
    lastOppenentName = nameOpponent;
    this->accept();
}

void searchGameForm::init(){
    if(client == 0) this->reject();
    this->setWindowTitle("Идет поиск соперника");
    this->setMaximumHeight(heigthP);
    this->setMinimumHeight(heigthP);
    this->setMaximumWidth(widthP);
    this->setMinimumWidth(widthP);
    QVBoxLayout* main = new QVBoxLayout;
    this->setLayout(main);
    main->addWidget(new WaiterWidget());
    connect(client, SIGNAL(gameFound(quint8, QString)), this, SLOT(gameFound(quint8, QString)));
}

int searchGameForm::exe1c(){
    client->searchGame();
    return this->exec();
}
