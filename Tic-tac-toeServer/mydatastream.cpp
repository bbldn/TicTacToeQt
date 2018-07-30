#include "mydatastream.h"

#include <QMessageBox>
#include <QDebug>

void MyDataStream::seeek(){
    if(state == false) return;
    quint64 pos = stream->device()->pos();
    stream->device()->seek(0);
    stream->operator<<((quint16)(length() - sizeof(qint16)));
    stream->device()->seek(pos);
}

MyDataStream::MyDataStream(QByteArray* a, QIODevice::OpenMode mode){
    stream = new QDataStream(a, mode);
    state = false;
    if(mode == QIODevice::WriteOnly) {
        stream->operator<<((qint16)0);
        state = true;
    }
}

QIODevice* MyDataStream::device() const{ return stream->device(); }
int MyDataStream::length(){ return (this->device() != 0) ? this->device()->size(): -1; }

bool MyDataStream::isCorrect(){
    if(state == true) return false;
    quint16 length;
    quint64 pos = stream->device()->pos();
    stream->device()->seek(0);
    stream->operator>>(length);
    if(pos > 0) stream->device()->seek(pos);
    return (length == (stream->device()->size() - sizeof(quint16)))? true: false;
}

MyDataStream& MyDataStream::operator<<(qint8 i){
    stream->operator<<(i);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(bool i){
    stream->operator<<(i);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(quint8 i){
    stream->operator<<(i);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(quint16 i){
    stream->operator<<(i);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(qint16 i){
    stream->operator<<(i);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(qint32 i){
    stream->operator<<(i);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(quint64 i){
    stream->operator<<(i);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(qint64 i){
    stream->operator<<(i);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(quint32 i){
    stream->operator<<(i);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(float f){
    stream->operator<<(f);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(double f){
    stream->operator<<(f);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(const char* s){
    stream->operator<<(s);
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator<<(QString s){
    stream->operator<<(s.toStdString().c_str());
    seeek();
    return *this;
}

MyDataStream &MyDataStream::operator>>(qint8& i){
    stream->operator>>(i);
    return *this;
}

MyDataStream &MyDataStream::operator>>(bool& i){
    stream->operator>>(i);
    return *this;
}

MyDataStream &MyDataStream::operator>>(quint8& i){
    stream->operator>>(i);
    return *this;
}

MyDataStream &MyDataStream::operator>>(quint16& i){
    stream->operator>>(i);
    return *this;
}

MyDataStream &MyDataStream::operator>>(qint16& i){
    stream->operator>>(i);
    return *this;
}

MyDataStream &MyDataStream::operator>>(quint32& i){
    stream->operator>>(i);
    return *this;
}

MyDataStream &MyDataStream::operator>>(qint32& i){
    stream->operator>>(i);
    return *this;
}

MyDataStream &MyDataStream::operator>>(quint64& i){
    stream->operator>>(i);
    return *this;
}

MyDataStream &MyDataStream::operator>>(qint64& i){
    stream->operator>>(i);
    return *this;
}

MyDataStream &MyDataStream::operator>>(float& f){
    stream->operator>>(f);
    return *this;
}

MyDataStream &MyDataStream::operator>>(double& f){
    stream->operator>>(f);
    return *this;
}

MyDataStream &MyDataStream::operator>>(char*& s){
    stream->operator>>(s);
    return *this;
}

MyDataStream &MyDataStream::operator>>(QString& s){
    char* str;
    stream->operator>>(str);
    s = str;
    return *this;
}

MyDataStream &MyDataStream::operator=(MyDataStream &obj){
    stream = obj.stream;
    return *this;
}
