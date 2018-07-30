#include "loggerwidget.h"

void LoggerWidget::init(){
    this->setReadOnly(true);
}

void LoggerWidget::addText(QString text){
    this->text += "[" + QDateTime::currentDateTime().toString() + "] " + text + "\n";
    this->setText(this->text);
}

LoggerWidget::LoggerWidget(QWidget* parent): QTextEdit(parent){
    init();
}
