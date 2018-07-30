#ifndef MYDATASTREAM_H
#define MYDATASTREAM_H

#include <QDataStream>

class MyDataStream{
    protected:
        QDataStream* stream;
        bool state;
        void seeek();
    public:
        MyDataStream(QByteArray* a, QIODevice::OpenMode mode);
        QIODevice* device() const;
        int length();
        bool isCorrect();
        MyDataStream& operator<<(qint8 i);
        MyDataStream& operator<<(bool i);
        MyDataStream& operator<<(quint8 i);
        MyDataStream& operator<<(quint16 i);
        MyDataStream& operator<<(qint16 i);
        MyDataStream& operator<<(qint32 i);
        MyDataStream& operator<<(quint64 i);
        MyDataStream& operator<<(qint64 i);
        MyDataStream& operator<<(quint32 i);
        MyDataStream& operator<<(float f);
        MyDataStream& operator<<(double f);
        MyDataStream& operator<<(const char* s);
        MyDataStream& operator<<(QString s);

        MyDataStream& operator>>(qint8& i);
        MyDataStream& operator>>(bool& i);
        MyDataStream& operator>>(quint8& i);
        MyDataStream& operator>>(quint16& i);
        MyDataStream& operator>>(qint16& i);
        MyDataStream& operator>>(quint32& i);
        MyDataStream& operator>>(qint32& i);
        MyDataStream& operator>>(quint64& i);
        MyDataStream& operator>>(qint64& i);
        MyDataStream& operator>>(float& f);
        MyDataStream& operator>>(double& f);
        MyDataStream& operator>>(char*& s);
        MyDataStream& operator>>(QString& s);
        MyDataStream& operator=(MyDataStream& obj);
};

#endif // MYDATASTREAM_H
