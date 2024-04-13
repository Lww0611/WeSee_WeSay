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
    QSqlQuery queryindex;

    //Data* getDetile(QString name);

    //表格形式的相关接口
    PeoPleBaseInfo* getBaseInfo(QString name);
    PeoPleBaseInfo* getBaseInfo(qint64 personid);

    LIST_Alias* getAliasList(QString name);
    LIST_Alias* getAliasList(qint64 personid);

    LIST_AddressList* getAddressList(QString name);
    LIST_AddressList* getAddressList(qint64 personid);

    LIST_OfficialList* getOfficialList(QString name);
    LIST_OfficialList* getOfficialList(qint64 personid);

    LIST_ListOfOfficals* getListOfOfficals(QString name);
    LIST_ListOfOfficals* getListOfOfficals(qint64 personid);

    LIST_DivisSocial* getDivisSocial(QString name);
    LIST_DivisSocial* getDivisSocial(qint64 personid);

    LIST_FamillyRelation* getFamillyRelation(QString name);
    LIST_FamillyRelation* getFamillyRelation(qint64 personid);

    LIST_SocialRelation* getSocialRelation(QString name);
    LIST_SocialRelation* getSocialRelation(qint64 personid);

    LIST_ZhuShu* getZhuShu(QString name);
    LIST_ZhuShu* getZhuShu(qint64 personid);

    LIST_Provenance* getProvenance(QString name);
    LIST_Provenance* getProvenance(qint64 personid);



    //获取全部关系
    QStringList* getRelationship(QString name);
    QStringList* getRelationship(qint64 personid);
    //获取社会关系类
    QStringList* getAssociations(QString name);
    QStringList* getAssociations(qint64 personid);
    //获取学术关系类
    QStringList* getScholarship(QString name);
    QStringList* getScholarship(qint64 personid);
    //获取朋友关系类
    QStringList* getFriendship(QString name);
    QStringList* getFriendship(qint64 personid);
    //获取政治关系类
    QStringList* getPolitics(QString name);
    QStringList* getPolitics(qint64 personid);
    //获取著述关系类
    QStringList* getWritings(QString name);
    QStringList* getWritings(qint64 personid);
    //获取军事关系类
    QStringList* getMilitary(QString name);
    QStringList* getMilitary(qint64 personid);
    //获取医疗关系类
    QStringList* getMedicine(QString name);
    QStringList* getMedicine(qint64 personid);
    //获取宗教关系类
    QStringList* getReligion(QString name);
    QStringList* getReligion(qint64 personid);
    //获取家庭关系类
    QStringList* getFamily(QString name);
    QStringList* getFamily(qint64 personid);
    //获取财务关系类
    QStringList* getFinance(QString name);
    QStringList* getFinance(qint64 personid);



};

#endif // DATACONTROL_H
