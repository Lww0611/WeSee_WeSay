#ifndef ADDRESS_H
#define ADDRESS_H
#include <QString>

typedef class Address
{
public:
    Address();

    //序号
    int index;
    //类型
    QString type;
    //名字
    QString name;
    //始年
    int firstyear;
    //终年
    int lastyear;
    //备注
    QString note;

    Address* next;


}Address, *Addressptr;

#endif // ADDRESS_H
