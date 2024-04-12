#ifndef DATACONTROL_H
#define DATACONTROL_H
#include <QString>
#include <QDate>
#include <QDebug>
#include <QtSql>
#include "Person.h"
#include "Data.h"


class DataControl
{
public:
    DataControl();
    ~DataControl();

    QSqlDatabase db;
    QSqlQuery query;

    Data* getDetile(QString name);


    //获取全部关系
    Personptr getRelationship(QString name);
    //获取社会关系类
    Personptr getAssociations(QString name);
    //获取学术关系类
    Personptr getScholarship(QString name);
    //获取朋友关系类
    Personptr getFriendship(QString name);
    //获取政治关系类
    Personptr getPolitics(QString name);
    //获取著述关系类
    Personptr getWritings(QString name);
    //获取军事关系类
    Personptr getMilitary(QString name);
    //获取医疗关系类
    Personptr getMedicine(QString name);
    //获取宗教关系类
    Personptr getReligion(QString name);
    //获取家庭关系类
    Personptr getFamily(QString name);
    //获取财务关系类
    Personptr getFinance(QString name);



};

#endif // DATACONTROL_H
