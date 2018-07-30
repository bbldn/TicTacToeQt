#include "lastpartyform.h"

void lastPartyForm::init(){
    mainWidget = new QVBoxLayout;
    this->setLayout(mainWidget);
    waiterWidget = new WaiterWidget;
    mainWidget->addWidget(waiterWidget);
    table = new QTableWidget;
    table->setColumnCount(1);
    table->setHorizontalHeaderItem(0, new QTableWidgetItem("Номер партии"));
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    connect(client, SIGNAL(GettingLastPartyFinished(QVector<QString>*)), this, SLOT(GettingLastPartyFinished(QVector<QString>*)));
    connect(table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(CellDoubleClicked(int,int)));
}

lastPartyForm::lastPartyForm(QDialog *parent, MyClient* client, Field* field): QDialog(parent){
    this->client = client;
    this->field = field;
    init();
}

int lastPartyForm::exe1c(){
    client->getLastParty();
    return exec();
}

void lastPartyForm::GettingLastPartyFinished(QVector<QString>* vect){
    this->vect = vect;
    mainWidget->removeWidget(waiterWidget);
    mainWidget->insertWidget(0, table);
    table->setRowCount(vect->length());
    for(int i = 0; i < vect->length(); i++)
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
}

void lastPartyForm::CellDoubleClicked(int x, int y){
    if(y < 0 || y >= vect->length()) return;
    x++;
    QStringList tmp = vect->takeAt(y).split(',');
    if(tmp.length() != 9) return;
    for(int i = 0, l = 0; i < 3; i++)
        for(int j = 0; j < 3; j++, l++)
            field->setCellState(i, j, atoi(tmp[l].toStdString().c_str()));
    this->accept();
}
