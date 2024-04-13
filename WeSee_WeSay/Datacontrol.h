#ifndef DATACONTROL_H
#define DATACONTROL_H
#include <QString>
#include <QDate>
#include <QDebug>
#include <QtSql>
#include "ProjectPeopleOfAllAgesCommon.h"


class DataControl
{
public:
    DataControl();
    ~DataControl();

    QSqlDatabase db;
    QSqlQuery query;

    //Data* getDetile(QString name);

    //表格形式的相关接口
    PeoPleBaseInfo* getBaseInfo(QString name);
    LIST_Alias* getAliasList(QString name);
    LIST_AddressList* getAddressList(QString name);
    LIST_OfficialList* getOfficialList(QString name);
    LIST_ListOfOfficals* getListOfOfficals(QString name);
    LIST_DivisSocial* getDivisSocial(QString name);
    LIST_FamillyRelation* getFamillyRelation(QString name);
    LIST_SocialRelation* getSocialRelation(QString name);
    LIST_ZhuShu* getZhuShu(QString name);
    LIST_Provenance* getProvenance(QString name);

    //获取全部关系
    QStringList* getRelationship(QString name);
    //获取社会关系类
    QStringList* getAssociations(QString name);
    //获取学术关系类
    QStringList* getScholarship(QString name);
    //获取朋友关系类
    QStringList* getFriendship(QString name);
    //获取政治关系类
    QStringList* getPolitics(QString name);
    //获取著述关系类
    QStringList* getWritings(QString name);
    //获取军事关系类
    QStringList* getMilitary(QString name);
    //获取医疗关系类
    QStringList* getMedicine(QString name);
    //获取宗教关系类
    QStringList* getReligion(QString name);
    //获取家庭关系类
    QStringList* getFamily(QString name);
    //获取财务关系类
    QStringList* getFinance(QString name);



};

#endif // DATACONTROL_H
