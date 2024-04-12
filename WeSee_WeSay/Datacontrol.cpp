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

Data *DataControl::getDetile(QString name)
{
//    //数据域
//    int personid;
//    QString name;
//    int birthday;
//    int deathday;
//    int age;
//    bool gender;

//    Altnameptr altnamelist;
//    Addressptr addresslist;
//    Entryptr entrylist;
//    Textptr textlist;
    Data* persondata = new Data();
    persondata->name = name;
    query.exec(QString("select c_personid, c_birthyear, c_deathyear, c_female from biog_main where c_name_chn = \"%1\"").arg(name));
    query.next();
    persondata->personid = query.value(0).toInt();
    if(query.value(1) != NULL)
    {
        persondata->birthday = query.value(1).toInt();
    }else
    {
        persondata->birthday = 0;
    }
    if(query.value(2) != NULL)
    {
        persondata->deathday = query.value(2).toInt();
    }else
    {
        persondata->deathday = 0;
    }
    if(query.value(1) != NULL && query.value(2) != NULL)
    {
        persondata->age = persondata->deathday - persondata->birthday;
    }
    persondata->gender = query.value(3).toBool();

    query.exec(QString("select c_alt_name_chn, c_notes, c_name_type_desc_chn from altname_data where c_personid = %1 join altname_codes on altname_data.c_alt_name_type_code = altname_codes.c_name_type_code").arg(persondata->personid));
    while(query.next())
    {
        Altnameptr newamtname = new Altname();
        newamtname->name = query.value(0).toString();
        newamtname->note = query.value(1).toString();
        newamtname->index = ++(persondata->altnamenum);
        newamtname->type = query.value(2).toString();
        newamtname->next = persondata->altnamelist->next;
        persondata->altnamelist->next = newamtname;
    }

    query.exec(QString("select c_firstyear, c_lastyear, c_notes, c_addr_desc_chn, c_name_chn from biog_addr_data where c_personid = %1 join biog_addr_codes on biog_addr_data.c_addr_id = biog_addr_codes.c_addr_id join addr_codes on biog_addr_data.c_addr_id = addr_codes.c_addr_id").arg(persondata->personid));
    while(query.next())
    {
        Addressptr newaddress = new Address();
        newaddress->name = query.value(4).toString();
        newaddress->type = query.value(3).toString();
        newaddress->note = query.value(2).toString();
        if(query.value(1) != NULL)
        {
            newaddress->firstyear = query.value(1).toInt();
        }
        if(query.value(0) != NULL)
        {
            newaddress->lastyear = query.value(0).toInt();
        }
        newaddress->index = ++(persondata->addressnum);
        newaddress->next = persondata->addresslist->next;
        persondata->addresslist->next = newaddress;
    }

    query.exec(QString("select c_notes, c_entry_desc_chn, c_entry_type_desc_chn from entry_data where c_personid = %1 join entry_codes on entry_data.c_entry_code = entry_codes.c_entry_code join entry_code_type_rel on entry_data.c_entry_code = entry_code_type_rel.c_entry_code join entry_types on entry_code_type_rel.c_entry_type = entry_types.c_entry_type").arg(persondata->personid));
    while(query.next())
    {
        Entryptr newentry = new Entry();
        newentry->note = query.value(0).toString();
        newentry->entryDesctype = query.value(1).toString();
        newentry->entryDesc = query.value(1).toString();
        newentry->index = ++(persondata->entrynum);
        newentry->next = persondata->entrylist->next;
        persondata->entrylist->next = newentry;
    }

    query.exec(QString("select c_notes, c_title_chn, c_role_desc_chn from biog_text_data where c_personid = %1 join text_codes on biog_text_data.c_textid = text_cedes.c_textid join text_bilicat_codes on text_codes.c_bibl_cat_code = text_bilicat_codes.c_text_cat_code join text_bilicat_code_type_rel on text_bilicat_codes.c_text_cat_code = text_bilicat_code_type_rel.c_text_cat_code join text_bilicat_types on text_bilicat_code_type_rel.c_text_cat_type_id = text_bilicat_types.c_text_cat_type_id join text_role_codes on biog_text_data.c_role_id = text_role_codes.c_role_id").arg(persondata->personid));
}

Personptr DataControl::getRelationship(QString name)
{

}

Personptr DataControl::getAssociations(QString name)
{

}

Personptr DataControl::getScholarship(QString name)
{

}

Personptr DataControl::getFriendship(QString name)
{

}

Personptr DataControl::getPolitics(QString name)
{

}

Personptr DataControl::getWritings(QString name)
{

}

Personptr DataControl::getMilitary(QString name)
{

}

Personptr DataControl::getMedicine(QString name)
{

}

Personptr DataControl::getReligion(QString name)
{

}

Personptr DataControl::getFamily(QString name)
{

}

Personptr DataControl::getFinance(QString name)
{

}
