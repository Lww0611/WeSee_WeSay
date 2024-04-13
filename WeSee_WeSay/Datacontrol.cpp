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
    PeoPleBaseInfo* info = new PeoPleBaseInfo();
    info->Name = name;

    query.exec(QString("SELECT c_personid, c_index_year, c_female, c_dy, c_birthyear, c_by_nh_code, c_deathyear, c_dy_nh_code, c_death_age FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();

    QString c_personid = query.value(0).toString();
    QString c_index_year = query.value(1).toString();
    bool c_female = query.value(2).toBool();
    QString c_dy = query.value(3).toString();
    QString c_birthyear = query.value(4).toString();
    QString c_by_nh_code = query.value(5).toString();
    QString c_deathyear = query.value(6).toString();
    QString c_dy_nh_code = query.value(7).toString();
    QString c_death_age = query.value(8).toString();

    info->PersonID = c_personid;
    info->NaImputedBirth = c_index_year;
    if(c_female)
    {
        info->Sex = "女";
    }else
    {
        info->Sex = "男";
    }
    query.exec(QString("SELECT c_dynasty_chn FROM DYNASTIES WHERE c_dy = %1").arg(c_dy));
    query.next();
    info->Time = query.value(0).toString();

    query.exec(QString("SELECT c_alt_name_chn FROM ALTNAME_DATA WHERE c_personid = %1").arg(c_personid));
    while(query.next())
    {
        info->Alias += query.value(0).toString();
        info->Alias += " ";
    }

    query.exec(QString("SELECT c_dynasty_chn, c_nianhao_chn FROM NIAN_HAO WHERE c_nianhao_id = %1").arg(c_by_nh_code));
    query.next();
    info->Birth += query.value(0).toString() + " " + query.value(1).toString() + "(" + c_birthyear + ")";

    query.exec(QString("SELECT c_dynasty_chn, c_nianhao_chn FROM NIAN_HAO WHERE c_nianhao_id = %1").arg(c_dy_nh_code));
    query.next();
    info->DeathDays += query.value(0).toString() + " " + query.value(1).toString() + "(" + c_deathyear + ")";

    info->DieAtTheAge = c_death_age;

    //籍贯、郡望找不到
    info->NativePlace = "";
    info->Krorimaki = "";

    return info;
}

QList<AliasList> *DataControl::getAliasList(QString name)
{
    QList<AliasList>* aliaslist = new QList<AliasList>;
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    int personid = query.value(0).toInt();
    query.exec(QString("SELECT c_alt_name_chn, c_alt_name_type_code, c_notes FROM ALTNAME_DATA WHERE c_personid = %1").arg(personid));
    int i = 1;
    while(query.next())
    {
        AliasList* alias = new AliasList;
        alias->Number = i++;
        alias->Nmae = query.value(0).toString();
        alias->Comment = query.value(2).toString();
        queryindex.exec(QString("SELECT c_name_type_desc_chn FROM ALTNAME_CODES WHERE c_name_type_code = %1").arg(query.value(1).toString()));
        queryindex.next();
        alias->Type = queryindex.value(0).toString();
        aliaslist->push_back(*alias);
    }
    return aliaslist;
}

QList<AddressList> *DataControl::getAddressList(QString name)
{
    QList<AddressList>* addressList = new QList<AddressList>;
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    int personid = query.value(0).toInt();
    query.exec(QString("SELECT c_addr_id, c_addr_type FROM BIOG_ADDR_DATA WHERE c_personid = %1").arg(personid));
    int i = 1;
    while(query.next())
    {
        AddressList* address = new AddressList;
        address->Number = i++;
        queryindex.exec(QString("SELECT c_name_chn, c_firstyear, c_lastyear FROM ADDR_CODES WHERE c_addr_id = %1").arg(query.value(0).toInt()));
        queryindex.next();
        address->Nmae = queryindex.value(0).toString();
        address->Birth = queryindex.value(1).toString();
        address->DeathDays = queryindex.value(2).toString();
        queryindex.exec(QString("SELECT c_addr_desc_chn FROM BIOG_ADDR_CODES WHERE c_addr_type = %1").arg(query.value(1).toString()));
        queryindex.next();
        address->Type = queryindex.value(0).toString();
        addressList->push_back(*address);
    }
    return addressList;
}

QList<OfficialList> *DataControl::getOfficialList(QString name)
{
    QList<OfficialList>* officialList = new QList<OfficialList>;
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    int personid = query.value(0).toInt();
    query.exec(QString("SLECT c_entry_code, c_notes, c_source FROM ENTRY_DATA WHERE c_personid = %1").arg(personid));
    int i = 1;
    while(query.next())
    {
        OfficialList* official = new OfficialList;
        official->Number = i++;
        official->Comment = query.value(1).toString();
        queryindex.exec(QString("SELECT c_entry_desc_chn FROM ENTRY_CODES WHERE c_entry_code = %1").arg(query.value(0).toString()));
        queryindex.next();
        official->OfficialDiff = queryindex.value(0).toString();
        queryindex.exec(QString("SELECT c_entry_type FROM ENTRY_CODE_TYPE_REL WHERE c_entry_code = %1").arg(query.value(0).toString()));
        queryindex.next();
        QString entry_type = queryindex.value(0).toString();
        queryindex.exec(QString("SELECT c_entry_type_desc_chn FROM ENTRY_TYPES WHERE c_entry_type = '%1'").arg(entry_type));
        queryindex.next();
        official->OfficialDoor = queryindex.value(0).toString();
        queryindex.exec(QString("SLELECT c_title_chn FROM TEXT_CODES WHERE c_textid = %1").arg(query.value(2).toString()));
        queryindex.next();
        official->OfficialAddress = queryindex.value(0).toString();
    }
    return officialList;
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


