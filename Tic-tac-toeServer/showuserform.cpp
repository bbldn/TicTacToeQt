#include "showuserform.h"
#include <QHeaderView>

void ShowUserForm::init(){
    this->resize(400, 400);
    this->setWindowTitle("Пользователи");
    QVBoxLayout* main = new QVBoxLayout;
    this->setLayout(main);
    table = new QTableWidget;
    table->setColumnCount(1);
    table->setHorizontalHeaderItem(0, new QTableWidgetItem("Пользователи"));
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    connect(table, SIGNAL(cellClicked(int, int)), this, SLOT(cellClicked(int, int)));
    main->addWidget(table);
    QPushButton* add = new QPushButton("Добавить");
    main->addWidget(add);
    connect(add, SIGNAL(released()), this, SLOT(add()));
    QPushButton* remove = new QPushButton("Удалить", this);
    main->addWidget(remove);
    connect(remove, SIGNAL(released()), this, SLOT(remove()));
    QPushButton* change = new QPushButton("Изменить пароль", this);
    main->addWidget(change);
    connect(change, SIGNAL(released()), this, SLOT(change()));
    addfrm = new addUserForm;
    changeForm = new changePasswordForm;
    id = -1;
    initBD();
}

void ShowUserForm::initBD(){
    vect = bd->getAllFromUsers();
    table->setRowCount(vect->length());
    for(int i = 0; i < vect->length(); i++)
        table->setItem(i, 0, new QTableWidgetItem(vect->operator [](i)));

}

ShowUserForm::ShowUserForm(QWidget *parent, BDController *bd) : QDialog(parent){
    this->bd = bd;
    init();
}

void ShowUserForm::add(){
    if(addfrm->exec() == QDialog::Accepted){
        QString login = addfrm->getLastLogin();
        QString password = addfrm->getLastPassword();
        if(bd->isExistUser(login) == false){
            bd->registerNewUser(login, password);
            vect->push_back(login);
            table->setRowCount(vect->length());
            table->setItem(vect->length() - 1, 0, new QTableWidgetItem(login));
        }else{
            QMessageBox error;
            error.setText("Пользователь с таким именем уже существует!");
            error.exec();
        }
    }
}

void ShowUserForm::remove(){
    if(id != -1){
        bd->removeUser(vect->operator [](id));
        table->removeRow(id);
        id = -1;
    }else{
        QMessageBox error;
        error.setText("С начало выберите пользователя!");
        error.exec();
    }
}

void ShowUserForm::change(){
    if(id == -1){
        QMessageBox error;
        error.setText("С начало выберите пользователя!");
        error.exec();
        return;
    }
    if(changeForm->exec() == QDialog::Accepted)
        bd->changePassword(vect->operator [](id), changeForm->getLastPassword());

}

void ShowUserForm::cellClicked(int row, int column){
    id = column;
    id = row;
}
