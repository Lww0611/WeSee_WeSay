#include "Datacontrol.h"



DataControl::DataControl()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString currentPath = QCoreApplication::applicationDirPath();
qDebug() << currentPath;
    QFileInfo fileInfo;
    fileInfo.setFile(currentPath);
    QString rootPath;
    rootPath= fileInfo.absolutePath();
    fileInfo.setFile(rootPath);
    rootPath= fileInfo.absolutePath();
qDebug() << rootPath;
    db.setDatabaseName(rootPath + "/WeSee_WeSay/recources/latest.db");

    if (!db.open()) {
        qDebug() << "Error: Failed to open database:" << db.lastError().text();
        exit(1);
    }

    query = QSqlQuery(db);
    queryindex = QSqlQuery(db);
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

    return info;
}

PeoPleBaseInfo *DataControl::getBaseInfo(qint64 personid)
{
    query.exec(QString("SELECT c_name_chn FROM BIOG_MAIN WHERE c_personid = %1").arg(personid));
    query.next();
    return getBaseInfo(query.value(0).toString());
}

QList<AliasList> *DataControl::getAliasList(QString name)
{
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getAliasList(personid);
}

QList<AliasList> *DataControl::getAliasList(qint64 personid)
{
    QList<AliasList>* aliaslist = new QList<AliasList>;
    query.exec(QString("SELECT c_alt_name_chn, c_alt_name_type_code, c_notes FROM ALTNAME_DATA WHERE c_personid = %1").arg(personid));
    int i = 1;
    while(query.next())
    {
        AliasList* alias = new AliasList;
        alias->Number = i++;
        alias->Name = query.value(0).toString();
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
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getAddressList(personid);
}

QList<AddressList> *DataControl::getAddressList(qint64 personid)
{
    QList<AddressList>* addressList = new QList<AddressList>;
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
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getOfficialList(personid);
}

QList<OfficialList> *DataControl::getOfficialList(qint64 personid)
{
    QList<OfficialList>* officialList = new QList<OfficialList>;

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
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getListOfOfficals(personid);
}

QList<ListOfOfficals> *DataControl::getListOfOfficals(qint64 personid)
{
    QList<ListOfOfficals>* listOfOfficals = new QList<ListOfOfficals>;

    query.exec(QString("SELECT c_posting_id FROM POSTING_DATA WHERE c_personid = %1").arg(personid));
    int i = 1;
    while(query.next())
    {
        ListOfOfficals* Officals = new ListOfOfficals;
        Officals->Number = i++;
        queryindex.exec(QString("SELECT c_office_id, c_firstyear, c_fy_nh_code, c_lastyear, c_ly_nh_code, c_appt_type_code, c_source, c_notes FROM POSTED_TO_OFFICE_DATA WHERE c_posting_id = %1").arg(query.value(0).toString()));
        queryindex.next();
        QString c_office_id = queryindex.value(0).toString();
        QString c_firstyear = queryindex.value(1).toString();
        QString c_fy_nh_code = queryindex.value(2).toString();
        QString c_lastyear = queryindex.value(3).toString();
        QString c_ly_nh_code = queryindex.value(4).toString();
        QString c_appt_type_code = queryindex.value(5).toString();
        QString c_source = queryindex.value(6).toString();
        QString c_notes = queryindex.value(7).toString();

        Officals->Comment = c_notes;

        queryindex.exec(QString("SELECT c_appt_type_desc_chn FROM APPOINTMENT_TYPE_CODES WHERE c_appt_type_code = %1").arg(c_appt_type_code));
        queryindex.next();
        Officals->DisgrantClass = queryindex.value(0).toString();

        queryindex.exec(QString("SELECT c_office_chn FROM OFFICE_CODES WHERE c_office_id = %1").arg(c_office_id));
        queryindex.next();
        Officals->OfficialName = queryindex.value(0).toString();

        queryindex.exec(QString("SELECT c_addr_id FROM POSTED_TO_ADDR_DATA WHERE c_posting_id = %1").arg(query.value(0).toString()));
        queryindex.next();
        QString c_addr_id = queryindex.value(0).toString();
        queryindex.exec(QString("SELECT c_name_chn FROM ADDR_CODES WHERE c_addr_id = %1").arg(c_addr_id));
        queryindex.next();
        Officals->OfficialAddress = queryindex.value(0).toString();

        queryindex.exec(QString("SELECT c_nianhao_chn FROM NIAN_HAO WHERE c_nianhao_id = %1").arg(c_fy_nh_code));
        queryindex.next();
        Officals->OfficialTime += queryindex.value(0).toString() + "(" + c_firstyear + ") - ";
        queryindex.exec(QString("SELECT c_nianhao_chn FROM NIAN_HAO WHERE c_nianhao_id = %1").arg(c_ly_nh_code));
        queryindex.next();
        Officals->OfficialTime += queryindex.value(0).toString() + "(" + c_lastyear + ")";

        queryindex.exec(QString("SELECT c_title_chn FROM TEXT_CODES WHERE c_textid = %1").arg(c_source));
        queryindex.next();
        Officals->Address = queryindex.value(0).toString();

        listOfOfficals->push_back(*Officals);
    }
    return listOfOfficals;
}

QList<DivisSocial> *DataControl::getDivisSocial(QString name)
{
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getDivisSocial(personid);
}

QList<DivisSocial> *DataControl::getDivisSocial(qint64 personid)
{
    QList<DivisSocial>* divisSociallist = new QList<DivisSocial>;

    query.exec(QString("SELECT c_status_code, c_firstyear, c_fy_nh_code, c_lastyear, c_ly_nh_code, c_source, c_notes FROM STATUS_DATA WHERE c_personid = %1").arg(personid));
    int i = 1;
    while(query.next())
    {
        DivisSocial* divisSocial = new DivisSocial;
        divisSocial->Number = i++;
        divisSocial->Comment = query.value(6).toString();
        queryindex.exec(QString("SELECT c_status_desc_chn FROM STATUS_CODES WHERE c_status_code = %1").arg(query.value(0).toString()));
        queryindex.next();
        divisSocial->SocialDivis = queryindex.value(0).toString();

        queryindex.exec(QString("SELECT c_title_chn FROM TEXT_CODES WHERE c_textid = %1").arg(query.value(5).toString()));
        queryindex.next();
        divisSocial->Address = queryindex.value(0).toString();

        queryindex.exec(QString("SELECT c_nianhao_chn FROM NIAN_HAO WHERE c_nianhao_id = %1").arg(query.value(2).toString()));
        queryindex.next();
        divisSocial->Time += queryindex.value(0).toString() + "(" + query.value(1).toString() + ") - ";
        queryindex.exec(QString("SELECT c_nianhao_chn FROM NIAN_HAO WHERE c_nianhao_id = %1").arg(query.value(4).toString()));
        queryindex.next();
        divisSocial->Time += queryindex.value(0).toString() + "(" + query.value(3).toString() + ")";

        divisSociallist->push_back(*divisSocial);
    }
    return divisSociallist;
}

QList<FamillyRelation> *DataControl::getFamillyRelation(QString name)
{
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getFamillyRelation(personid);
}

QList<FamillyRelation> *DataControl::getFamillyRelation(qint64 personid)
{
    QList<FamillyRelation>* famillyRelationlist = new QList<FamillyRelation>;

    query.exec(QString("SELECT c_kin_id, c_kin_code, c_source, c_notes FROM KIN_DATA WHERE c_personid = %1").arg(personid));
    int i = 1;
    while(query.next())
    {
        FamillyRelation* famillyRelation = new FamillyRelation;
        famillyRelation->Number = i++;
        famillyRelation->Comment = query.value(3).toString();
        queryindex.exec(QString("SELECT c_name_chn FROM BIOG_MAIN WHERE c_personid = %1").arg(query.value(0).toString()));
        queryindex.next();
        famillyRelation->RelationPerson = queryindex.value(0).toString();

        queryindex.exec(QString("SELECT c_kinrel_chn FROM KINSHIP_CODES WHERE c_kincode = %1").arg(query.value(1).toString()));
        queryindex.next();
        famillyRelation->Relation = queryindex.value(0).toString();

        queryindex.exec(QString("SELECT c_title_chn FROM TEXT_CODES WHERE c_textid = %1").arg(query.value(2).toString()));
        queryindex.next();
        famillyRelation->Address = queryindex.value(0).toString();

        famillyRelationlist->push_back(*famillyRelation);
    }
    return famillyRelationlist;
}

QList<SocialRelation> *DataControl::getSocialRelation(QString name)
{
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getSocialRelation(personid);
}

QList<SocialRelation> *DataControl::getSocialRelation(qint64 personid)
{
    QList<SocialRelation>* SocialRelationlist = new QList<SocialRelation>;

    query.exec(QString("SELECT c_assoc_code, c_assoc_id, c_source, c_notes FROM ASSOC_DATA WHERE c_personid = %1").arg(personid));
    int i = 1;
    while(query.next())
    {
        SocialRelation* socialRelation = new SocialRelation;
        socialRelation->Number = i++;
        socialRelation->Comment = query.value(3).toString();
        queryindex.exec(QString("SELECT c_assoc_type_id FROM ASSOC_CODE_TYPE_REL WHERE c_assoc_code = %1").arg(query.value(1).toString()));
        queryindex.next();
        QString c_assoc_type_id = queryindex.value(0).toString();
        queryindex.exec(QString("SELECT c_assoc_type_desc_chn FROM ASSOC_TYPES WHERE c_assoc_type_id = '%1'").arg(c_assoc_type_id));
        queryindex.next();
        socialRelation->Relation = queryindex.value(0).toString();
        queryindex.exec(QString("SELECT c_name_chn FROM BIOG_MAIN WHERE c_personid = %1").arg(query.value(1).toString()));
        queryindex.next();
        socialRelation->RelationPerson = queryindex.value(0).toString();
        queryindex.exec(QString("SELECT c_title_chn FROM TEXT_CODES WHERE c_textid = %1").arg(query.value(2).toString()));
        queryindex.next();
        socialRelation->Address = queryindex.value(0).toString();
        SocialRelationlist->push_back(*socialRelation);
    }
    return SocialRelationlist;
}

QList<ZhuShu> *DataControl::getZhuShu(QString name)
{
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getZhuShu(personid);
}

QList<ZhuShu> *DataControl::getZhuShu(qint64 personid)
{
    QList<ZhuShu>* zhuShulist = new QList<ZhuShu>;

    query.exec(QString("SELECT c_textid, c_role_id, c_notes FROM BIOG_TEXT_DATA WHERE c_personid = %1").arg(personid));
    int i = 1;
    while(query.next())
    {
        ZhuShu* zhuShu = new ZhuShu;
        zhuShu->Number = i++;
        zhuShu->Comment = query.value(2).toString();
        queryindex.exec(QString("SELECT c_title_chn, c_text_year FROM TEXT_CODES WHERE c_textid = %1").arg(query.value(0).toString()));
        queryindex.next();
        zhuShu->Production = queryindex.value(0).toString();
        zhuShu->ProductionTime = queryindex.value(1).toString();
        queryindex.exec(QString("SELECT c_role_desc_chn FROM TEXT_ROLE_CODES WHERE c_role_id = %1").arg(query.value(1).toString()));
        queryindex.next();
        zhuShu->Role = queryindex.value(0).toString();
        zhuShulist->push_back(*zhuShu);
    }
    return zhuShulist;
}

QList<Provenance> *DataControl::getProvenance(QString name)
{
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getProvenance(personid);
}

QList<Provenance> *DataControl::getProvenance(qint64 personid)
{
    QList<Provenance>* provenancelist = new QList<Provenance>;

    query.exec(QString("SELECT c_textid, c_notes FROM BIOG_SOURCE_DATA WHERE c_personid = %1").arg(personid));
    int i = 1;
    while(query.next())
    {
        Provenance* provenance = new Provenance;
        provenance->Number = i++;
        provenance->Comment = query.value(1).toString();
        queryindex.exec(QString("SELECT c_title_chn FROM TEXT_CODES WHERE c_textid = %1").arg(query.value(0).toString()));
        queryindex.next();
        provenance->Provenance_ = queryindex.value(0).toString();
        provenancelist->push_back(*provenance);
    }
    return provenancelist;
}

QStringList *DataControl::getRelationship(QString name)
{
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getRelationship(personid);
}

QStringList *DataControl::getRelationship(qint64 personid)
{
    QStringList* stringList = new QStringList;
    query.exec(QString("SELECT c_assoc_id FROM ASSOC_DATA WHERE c_personid = %1").arg(personid));
    while(query.next())
    {
        QString* info = new QString;
        queryindex.exec(QString("SELECT c_name_chn FROM BIOG_MAIN WHERE c_personid = %1").arg(query.value(0).toString()));
        queryindex.next();
        *info = queryindex.value(0).toString();
        stringList->push_back(*info);
    }
    return stringList;
}

QStringList *DataControl::getAssociations(QString name)
{
    QString role = "社會關係（籠統）";
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getAssociations(qint64 personid)
{
    QString role = "社會關係（籠統）";
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getScholarship(QString name)
{
    QString role = "學術關係類";
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getScholarship(qint64 personid)
{
    QString role = "學術關係類";
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getFriendship(QString name)
{
    QString role = "朋友關係類";
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getFriendship(qint64 personid)
{
    QString role = "朋友關係類";
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getPolitics(QString name)
{
    QString role = "政治關係類";
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getPolitics(qint64 personid)
{
    QString role = "政治關係類";
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getWritings(QString name)
{
    QString role = "著述關係類";
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getWritings(qint64 personid)
{
    QString role = "著述關係類";
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getMilitary(QString name)
{
    QString role = "軍事關係類";
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getMilitary(qint64 personid)
{
    QString role = "軍事關係類";
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getMedicine(QString name)
{
    QString role = "醫療關係類";
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getMedicine(qint64 personid)
{
    QString role = "醫療關係類";
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getReligion(QString name)
{
    QString role = "宗教關係類";
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getReligion(qint64 personid)
{
    QString role = "宗教關係類";
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getFamily(QString name)
{
    QString role = "家庭關係類";
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getFamily(qint64 personid)
{
    QString role = "家庭關係類";
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getFinance(QString name)
{
    QString role = "財務關係類";
    query.exec(QString("SELECT c_personid FROM BIOG_MAIN WHERE c_name_chn = '%1'").arg(name));
    query.next();
    qint64 personid = query.value(0).toInt();
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getFinance(qint64 personid)
{
    QString role = "財務關係類";
    return getrelationshipwithrole(personid, role);
}

QStringList *DataControl::getrelationshipwithrole(qint64 personid, QString role)
{
    QStringList* stringList = new QStringList;
    query.exec(QString("SELECT c_assoc_id, c_assoc_code FROM ASSOC_DATA WHERE c_personid = %1").arg(personid));
    while(query.next())
    {

        queryindex.exec(QString("SELECT c_assoc_type_id FROM ASSOC_CODE_TYPE_REL WHERE c_assoc_code = %1").arg(query.value(1).toString()));
        queryindex.next();
        QString c_assoc_type_id = queryindex.value(0).toString();
        queryindex.exec(QString("SELECT c_assoc_type_parent_id FROM ASSOC_TYPES WHERE c_assoc_type_id = '%1'").arg(c_assoc_type_id));
        queryindex.next();
        QString c_assoc_type_parent_id = queryindex.value(0).toString();;
        queryindex.exec(QString("SELECT c_assoc_type_desc_chn FROM ASSOC_TYPES WHERE c_assoc_type_id = '%1'").arg(c_assoc_type_parent_id));
        queryindex.next();
        if(queryindex.value(0).toString() == role)
        {
            queryindex.exec(QString("SELECT c_name_chn FROM BIOG_MAIN WHERE c_personid = %1").arg(query.value(0).toString()));
            queryindex.next();
            QString* info = new QString;
            *info = queryindex.value(0).toString();
            stringList->push_back(*info);
        }
    }
    return stringList;
}


