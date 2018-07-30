#ifndef FIELD_H
#define FIELD_H
#define COUNT 3

#include "cell.h"

#include <QGridLayout>
#include <QWidget>
#include <QMessageBox>

class Field: public QWidget{
    Q_OBJECT
    private:
        explicit Field(QWidget* parent = 0, QImage* image = 0);
    protected:
        QGridLayout* mainWidget;
        QImage* image;
        Cell*** cells;
        int state;//0 - uncertainty, 1 - We're cross, 2 - We're circle
        int oState;//opponent state
        bool lock;
        void init();

    public:
        static Field* getInstatce(QWidget* parent = 0, QImage* image = 0);
        void setCellState(int x, int y, int state);
        void checkField();
        void clean();
        void makeMove(int x, int y);
        void lockUp();
        void unLock();
        void setState(int state);
        void setCross();
        void setCircle();
        int getState();
        bool isLocked();
        bool isCross();
        bool isCircle();
    signals:
       void MadeMove(int x, int y);
    public slots:
       void CellClick(Cell* cell);
};

#endif // FIELD_H
