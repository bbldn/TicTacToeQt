#ifndef WAITERWIDGET_H
#define WAITERWIDGET_H
#define widthP 300
#define heigthP 283

#include <QTimer>
#include <QWidget>
#include <QPainter>

class WaiterWidget: public QWidget{
    Q_OBJECT
    protected:
        QTimer timer;
        QImage* image;
        int ii;
        void init();
    private:
        void paintEvent(QPaintEvent*);
    public:
        explicit WaiterWidget(QWidget* parent = 0);

    signals:

    public slots:
        void timeout();
};

#endif // WAITERWIDGET_H
