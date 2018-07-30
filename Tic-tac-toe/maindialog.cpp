#include "maindialog.h"

MainDialog::MainDialog(QWidget* parent, MyClient* client): QDialog(parent){
    this->client = client;
    init();
}

MainDialog::~MainDialog(){}

void MainDialog::init(){
    this->setMaximumHeight(420);
    this->setMaximumWidth(350);
    main = new QVBoxLayout();
    bar = new QMenuBar();
    oName = new QLabel(this);
    state = new QLabel("Состояние");
    main->addWidget(oName);
    main->addWidget(state);
    game = new QMenu("Игра");
    fieldM = new QMenu("Поле");
    QAction* records = new QAction("Рекорды");
    bar->addMenu(game);
    bar->addAction(records);
    bar->addMenu(fieldM);
    QAction* sAdversary = new QAction("Найти соперника");
    game->addAction(sAdversary);
    QAction* sLastGames = new QAction("Последнии 3 игры");
    QAction* cfield = new QAction("Очистить");
    fieldM->addAction(cfield);
    fieldM->addAction(sLastGames);
    main->setMenuBar(bar);
    this->setLayout(main);
    field = Field::getInstatce(this, new QImage("images/all.png"));
    main->addWidget(field);
    sForm = new searchGameForm(this, client);
    rForm = new showRecordsForm(this, client);
    connect(sAdversary, SIGNAL(triggered(bool)), this, SLOT(searchAdversary()));
    connect(sLastGames, SIGNAL(triggered(bool)), this, SLOT(showLastGame()));
    connect(cfield, SIGNAL(triggered(bool)), this, SLOT(cleanField()));
    connect(field, SIGNAL(MadeMove(int, int)), this, SLOT(MadeMove(int, int)));
    connect(client, SIGNAL(onDisconnect()), this, SLOT(onDisconnect()));
    connect(client, SIGNAL(OpponentMadeMove(int, int)), this, SLOT(OpponentMadeMove(int, int)));
    connect(client, SIGNAL(OpponentOff()), this, SLOT(OpponentOff()));
    connect(client, SIGNAL(Draw()), this, SLOT(Draw()));
    connect(client, SIGNAL(WeWon()), this, SLOT(WeWon()));
    connect(client, SIGNAL(WeLost()), this, SLOT(WeLost()));
    connect(records, SIGNAL(triggered(bool)), this, SLOT(showRecords()));
}

void MainDialog::onDisconnect(){
    QMessageBox error;
    error.setText("Сервер закрыл соединение");
    error.exec();
    this->reject();
}

void MainDialog::OpponentOff(){ outputStateGame("Ваш противник отключился"); }
void MainDialog::Draw(){ outputStateGame("Ничья"); }
void MainDialog::WeWon(){ outputStateGame("Поздравляем! Вы выйграли"); }
void MainDialog::WeLost(){ outputStateGame("Сожалеем, вы проиграли"); }

void MainDialog::searchAdversary(){
    if(sForm->exe1c() != QDialog::Accepted){
        client->endSearchGame();
        return;
    }
    fieldM->setEnabled(false);
    oName->setText("Соперник: " + sForm->getLastName());
    int tmp = sForm->getLastState();
    field->setState(tmp);
    field->clean();
    game->setEnabled(false);
    if(tmp == Cell::CROSS)
        OpponentMadeMove(-1, -1);
    else
        MadeMove(-1, -1);
}

void MainDialog::showRecords(){
    showRecordsForm rrForm(this, client);
    rrForm.exe1c();
}

void MainDialog::showLastGame(){
    lastPartyForm frm(NULL, client, field);
    frm.exe1c();
}

void MainDialog::cleanField(){ field->clean(); }

void MainDialog::MadeMove(int x, int y){
    field->lockUp();
    state->setText("Ожидайте хода соперника");
    client->sendMove(x, y);
}

void MainDialog::OpponentMadeMove(int x, int y){
    field->unLock();
    state->setText("Ваш ход");
    field->makeMove(x, y);
}

void MainDialog::outputStateGame(QString text){
    QMessageBox error;
    error.setText(text);
    error.exec();
    oName->clear();
    state->setText("Состояние");
    field->lockUp();
    game->setEnabled(true);
    fieldM->setEnabled(true);
}
