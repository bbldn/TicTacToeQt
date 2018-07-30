#include "waiterwidget.h"

void WaiterWidget::init(){
    this->resize(widthP, heigthP);
    image = new QImage("images/anim1.png");
    timer.setInterval(100);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    ii = 0;
    if(image != NULL) timer.start();
}

void WaiterWidget::paintEvent(QPaintEvent *){
    QPainter* p = new QPainter(this);
    if(ii == 12) ii = 0;
    //QRect target(0, 0, widthP, heigthP);
    QRect target(0, 0, this->width(), this->height());
    QRect sources(0, ii * heigthP, widthP, heigthP);
    p->drawImage(target, *image, sources);
    p->end();
    ii++;
}

WaiterWidget::WaiterWidget(QWidget *parent) : QWidget(parent){
    init();
}

void WaiterWidget::timeout(){ this->repaint(); }
