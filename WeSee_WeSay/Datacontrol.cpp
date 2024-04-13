#include "Datacontrol.h"



DataControl::DataControl()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:/QtProjects/历史人物/latest.db");

    if (!db.open()) {
        qDebug() << "Error: Failed to open database:" << db.lastError().text();
        exit(1);
    }
}

DataControl::~DataControl()
{
    db.close();
}

PeoPleBaseInfo *DataControl::getBaseInfo(QString name)
{

}

QList<AliasList> *DataControl::getAliasList(QString name)
{

}

QList<AddressList> *DataControl::getAddressList(QString name)
{

}

QList<OfficialList> *DataControl::getOfficialList(QString name)
{

}

QList<ListOfOfficals> *DataControl::getListOfOfficals(QString name)
{

}

QList<DivisSocial> *DataControl::getDivisSocial(QString name)
{

}

QList<FamillyRelation> *DataControl::getFamillyRelation(QString name)
{

}

QList<SocialRelation> *DataControl::getSocialRelation(QString name)
{

}

QList<ZhuShu> *DataControl::getZhuShu(QString name)
{

}

QList<Provenance> *DataControl::getProvenance(QString name)
{

}

QStringList *DataControl::getRelationship(QString name)
{

}

QStringList *DataControl::getAssociations(QString name)
{

}

QStringList *DataControl::getScholarship(QString name)
{

}

QStringList *DataControl::getFriendship(QString name)
{

}

QStringList *DataControl::getPolitics(QString name)
{

}

QStringList *DataControl::getWritings(QString name)
{

}

QStringList *DataControl::getMilitary(QString name)
{

}

QStringList *DataControl::getMedicine(QString name)
{

}

QStringList *DataControl::getReligion(QString name)
{

}

QStringList *DataControl::getFamily(QString name)
{

}

QStringList *DataControl::getFinance(QString name)
{

}


