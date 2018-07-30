#include "field.h"

void Field::init(){
    mainWidget = new QGridLayout();
    mainWidget->setHorizontalSpacing(-1);
    mainWidget->setVerticalSpacing(-1);
    this->setLayout(mainWidget);
    cells = new Cell**[COUNT];//указатель на массив ячеек
    for(int i = 0; i < COUNT; i++)
        cells[i] = new Cell*[COUNT];
    for(int i = 0; i < COUNT; i++){
        for(int j = 0; j < COUNT; j++){
            cells[i][j] = new Cell(NULL, image, i, j);
            connect(cells[i][j], SIGNAL(mousePressEvent(Cell*)), this, SLOT(CellClick(Cell*)));
            mainWidget->addWidget(cells[i][j], i, j);
        }
    }
    state = 0;
    lockUp();
}

Field *Field::getInstatce(QWidget *parent, QImage *image){
    static Field* field = new Field(parent, image);
    return field;
}

Field::Field(QWidget* parent, QImage* image): QWidget(parent){
    this->image = image;
    this->setMinimumHeight(sizet * COUNT);
    this->setMaximumHeight(sizet * COUNT);
    this->setMinimumWidth(sizet * COUNT);
    this->setMaximumWidth(sizet * COUNT);
    init();
}

void Field::setCellState(int x, int y, int state){
    if(x < 0 || x >= COUNT || y < 0 || y >= COUNT) return;
    cells[x][y]->setState(state);
    cells[x][y]->repaint();
    checkField();
}

void Field::checkField(){
    /*rows*/
    if(cells[0][2]->getState() == cells[0][1]->getState() && cells[0][1]->getState()  == cells[0][0]->getState() && cells[0][0]->getState() != 0){
        cells[0][2]->setStateStrikeout(2);
        cells[0][1]->setStateStrikeout(2);
        cells[0][0]->setStateStrikeout(2);
        cells[0][2]->repaint();
        cells[0][1]->repaint();
        cells[0][0]->repaint();
    }
    if(cells[1][2]->getState() == cells[1][1]->getState() && cells[1][1]->getState()  == cells[1][0]->getState() && cells[1][0]->getState() != 0){
        cells[1][2]->setStateStrikeout(2);
        cells[1][1]->setStateStrikeout(2);
        cells[1][0]->setStateStrikeout(2);
        cells[1][2]->repaint();
        cells[1][1]->repaint();
        cells[1][0]->repaint();
    }
    if(cells[2][2]->getState() == cells[2][1]->getState() && cells[2][1]->getState()  == cells[2][0]->getState() && cells[2][0]->getState() != 0){
        cells[2][2]->setStateStrikeout(2);
        cells[2][1]->setStateStrikeout(2);
        cells[2][0]->setStateStrikeout(2);
        cells[2][2]->repaint();
        cells[2][1]->repaint();
        cells[2][0]->repaint();
    }
    /*columns*/
    if(cells[2][0]->getState() == cells[1][0]->getState() && cells[1][0]->getState()  == cells[0][0]->getState() && cells[0][0]->getState() != 0){
        cells[2][0]->setStateStrikeout(1);
        cells[1][0]->setStateStrikeout(1);
        cells[0][0]->setStateStrikeout(1);
        cells[2][0]->repaint();
        cells[1][0]->repaint();
        cells[0][0]->repaint();
    }
    if(cells[2][1]->getState() == cells[1][1]->getState() && cells[1][1]->getState()  == cells[0][1]->getState() && cells[0][1]->getState() != 0){
        cells[2][1]->setStateStrikeout(1);
        cells[1][1]->setStateStrikeout(1);
        cells[0][1]->setStateStrikeout(1);
        cells[2][1]->repaint();
        cells[1][1]->repaint();
        cells[0][1]->repaint();
    }
    if(cells[2][2]->getState() == cells[1][2]->getState() && cells[1][2]->getState()  == cells[0][2]->getState() && cells[0][2]->getState() != 0){
        cells[2][2]->setStateStrikeout(1);
        cells[1][2]->setStateStrikeout(1);
        cells[0][2]->setStateStrikeout(1);
        cells[2][2]->repaint();
        cells[1][2]->repaint();
        cells[0][2]->repaint();
    }/*diagonals*/
    if(cells[2][2]->getState() == cells[1][1]->getState() && cells[1][1]->getState()  == cells[0][0]->getState() && cells[0][0]->getState() != 0){
        cells[2][2]->setStateStrikeout(3);
        cells[1][1]->setStateStrikeout(3);
        cells[0][0]->setStateStrikeout(3);
        cells[2][2]->repaint();
        cells[1][1]->repaint();
        cells[0][0]->repaint();
    }
    if(cells[2][0]->getState() == cells[1][1]->getState() && cells[1][1]->getState()  == cells[0][2]->getState() && cells[0][2]->getState() != 0){
        cells[2][0]->setStateStrikeout(4);
        cells[1][1]->setStateStrikeout(4);
        cells[0][2]->setStateStrikeout(4);
        cells[2][0]->repaint();
        cells[1][1]->repaint();
        cells[0][2]->repaint();
    }
}

void Field::clean(){
    for(int i = 0; i < COUNT; i++){
        for(int j = 0; j < COUNT; j++){
            cells[i][j]->setState(0);
            cells[i][j]->setStateStrikeout(0);
            cells[i][j]->repaint();
        }
    }
}

void Field::makeMove(int x, int y){
    if(x < 0 || x >= COUNT || y < 0 || y >= COUNT) return;
    cells[x][y]->setState(oState);
    cells[x][y]->repaint();
    checkField();
}

void Field::CellClick(Cell* cell){
    if(isLocked() || !cell->isEmpty()) return;
    cell->setState(state);
    cell->repaint();
    checkField();
    emit MadeMove(cell->getX(), cell->getY());
}

void Field::lockUp(){ lock = true; }
void Field::unLock(){ lock = false; }
int Field::getState(){ return state; }
bool Field::isLocked(){ return lock; }
bool Field::isCross(){ return state == Cell::CROSS; }
bool Field::isCircle(){ return state == Cell::CIRCLE; }

void Field::setCross(){
    state = Cell::CROSS;
    oState = Cell::CIRCLE;
}

void Field::setCircle(){
    state = Cell::CIRCLE;
    oState = Cell::CROSS;
}

void Field::setState(int state){
    this->state = state;
    oState = (state == 1)? 2: 1;
}

