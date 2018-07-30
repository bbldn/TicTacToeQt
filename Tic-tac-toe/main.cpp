#include "logininform.h"
#include "maindialog.h"
#include "searchgameform.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    loginInForm f;
    MainDialog w(0, f.getMyClient());
    if(f.exec() == QDialog::Accepted) w.show();
    else exit(0);
    return a.exec();
}
