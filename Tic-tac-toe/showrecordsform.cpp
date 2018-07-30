#include "showrecordsform.h"

void showRecordsForm::init(){
    this->resize(300, 300);
    main = new QVBoxLayout;
    ww = new WaiterWidget;
    main->addWidget(ww);
    QPushButton* ok = new QPushButton("OK");
    main->addWidget(ok);
    connect(ok, SIGNAL(clicked(bool)), this, SLOT(okPress()));
    connect(client, SIGNAL(GettingRecordsFinished(QVector<NameAndRecord>*)), this, SLOT(GettingRecordsFinished(QVector<NameAndRecord>*)));
    this->setLayout(main);
}

showRecordsForm::showRecordsForm(QDialog* parent, MyClient* client): QDialog(parent){
    this->client = client;
    init();
}

int showRecordsForm::exe1c(){
    client->getRecords();
    return exec();
}

void showRecordsForm::okPress(){
    this->accept();
}

void showRecordsForm::GettingRecordsFinished(QVector<NameAndRecord>* vect){
    QTableWidget* table = new QTableWidget;
    table->setColumnCount(2);
    table->setHorizontalHeaderItem(0, new QTableWidgetItem("Пользователи"));
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Кол-во побед"));
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->setRowCount(vect->length());
    main->removeWidget(ww);
    main->insertWidget(0, table);
    for(int i = 0; i < vect->length(); i++){
        table->setItem(i, 0, new QTableWidgetItem(vect->operator [](i).name));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(vect->operator [](i).record)));
    }
}
