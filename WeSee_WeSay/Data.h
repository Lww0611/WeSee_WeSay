#ifndef DATA_H
#define DATA_H
#include <QString>
#include "Altname.h"
#include "Address.h"
#include "Entry.h"
#include "Text.h"


class Data
{
public:
    Data();

    //数据域
    int personid;
    QString name;
    int birthday;
    int deathday;
    int age;
    bool gender;

    int altnamenum;
    Altnameptr altnamelist;
    int addressnum;
    Addressptr addresslist;
    int entrynum;
    Entryptr entrylist;
    int textnum;
    Textptr textlist;

};

#endif // DATA_H
