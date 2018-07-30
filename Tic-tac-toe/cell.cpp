#include "cell.h"

void Cell::paintEvent(QPaintEvent *){
    QPainter* p = new QPainter(this);
    switch (state) {
        case 0:
            if(image != NULL){
                QRect target(0, 0, sizet, sizet);
                QRect sources(stateStrikeout * sizet, 0, sizet, sizet);
                p->drawImage(target, *image, sources);
            }
            break;
        case 1:
            if(image != NULL){
                QRect target(0, 0, sizet, sizet);
                QRect sources(stateStrikeout * sizet, sizet, sizet, sizet);
                p->drawImage(target, *image, sources);
            }
            break;
        case 2:
            if(image != NULL){
                QRect target(0, 0, sizet, sizet);
                QRect sources(stateStrikeout * sizet, 2 * sizet, sizet, sizet);
                p->drawImage(target, *image, sources);
            }
            break;
        default:
            break;
    }
    p->end();
}

void Cell::init(){
    state = 0;
    stateStrikeout = 0;
}

Cell::Cell(QWidget* parent, QImage* image, int x, int y): QWidget(parent){
    this->image = image;
    this->setMinimumHeight(sizet);
    this->setMaximumHeight(sizet);
    this->setMinimumWidth(sizet);
    this->setMaximumWidth(sizet);
    this->x = x;
    this->y = y;
    init();
}

void Cell::setState(int state){ this->state = state; }
void Cell::setX(int value){ x = value; }
void Cell::setY(int value){ y = value; }
void Cell::setStateStrikeout(int value){ stateStrikeout = value; }
int Cell::getState(){ return state; }
int Cell::getX(){ return x; }
int Cell::getY(){ return y; }
int Cell::getStateStrikeout(){ return stateStrikeout; }
bool Cell::isEmpty(){ return state == 0; }
bool Cell::isCross(){ return state == 1; }
bool Cell::isCircle(){ return state == 2; }
void Cell::mousePressEvent(QMouseEvent* event){ emit mousePressEvent(this); }
