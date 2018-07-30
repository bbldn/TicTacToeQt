#ifndef CELL_H
#define CELL_H
#define sizet 100

#include <QWidget>
#include <QPainter>

class Cell: public QWidget{
    Q_OBJECT
    private:
        void paintEvent(QPaintEvent*);
        void mousePressEvent(QMouseEvent* event);
    protected:
        QImage* image;
        int state;//0 - empty, 1 - cross, 2 - circle
        int stateStrikeout;//0 - usually
        int x;
        int y;
        void init();
    public:
        const static int EMPTY = 0;
        const static int CROSS = 1;
        const static int CIRCLE = 2;
        explicit Cell(QWidget *parent = 0, QImage* image = 0, int x = -1, int y = -1);
        void setState(int state);
        void setX(int value);
        void setY(int value);
        void setStateStrikeout(int value);
        int getState();
        int getX();
        int getY();
        int getStateStrikeout();
        bool isEmpty();
        bool isCross();
        bool isCircle();
    signals:
        mousePressEvent(Cell* cell);
    public slots:
};

#endif // CELL_H
