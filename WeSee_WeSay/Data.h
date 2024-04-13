#ifndef DATA_H
#define DATA_H
#include <QString>


class Data
{
public:
    Data();
    int id;

    QString ToString();
    static Data FromString(QString s);
};

#endif // DATA_H
