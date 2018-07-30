#ifndef LOGGERWIDGET_H
#define LOGGERWIDGET_H

#include <QTextEdit>
#include <QDateTime>

class LoggerWidget : public QTextEdit{
    Q_OBJECT
    protected:
        QString text;
        void init();
    public:
        void addText(QString text);
        LoggerWidget(QWidget *parent);
};

#endif // LOGGERWIDGET_H
