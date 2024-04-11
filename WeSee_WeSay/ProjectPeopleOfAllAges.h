#pragma once

#include <QtWidgets/QWidget>
#include "ui_ProjectPeopleOfAllAges.h"
#include "ProjectPeopleOfAllAgesCommon.h"
#define MAXLABLECOUNT 6
class QTableWidget;
class ProjectPeopleOfAllAges : public QWidget
{
    Q_OBJECT

public:
    ProjectPeopleOfAllAges(QWidget *parent = nullptr);
    ~ProjectPeopleOfAllAges();
public:

    //表格形式的相关接口
    void setBaseInfo(const PeoPleBaseInfo& info);
    void setAliasList(const LIST_Alias& info);
    void setAddressList(const LIST_AddressList& info);
    void setOfficialList(const LIST_OfficialList& info);
    void setListOfOfficals(const LIST_ListOfOfficals& info);
    void setDivisSocial(const LIST_DivisSocial& info);
    void setFamillyRelation(const LIST_FamillyRelation& info);
    void setSocialRelation(const LIST_SocialRelation& info);
    void setZhuShu(const LIST_ZhuShu& info);
    void setProvenance(const LIST_Provenance& info);

    //关系图形式相关接口
    void setKindship(QStringList& info);
    void setSocialRelation(QStringList& info);
    void setAcademicRelation(QStringList& info);
    void setFriendRelation(QStringList& info);
    void setBibliographicRelation(QStringList& info);

private slots:
    void SignalPushButton_form();
    void SignalpushButton_relation();
    void SignalStateChanged(int);
    void SignalButtonClick();
private:
    void initConnect();
    void initUI();
    void setTableWidgetVisbal(QTableWidget*,int index = 0);
    void setTableWidgetVisbal(QWidget*, int index = 0);
private:
    Ui::ProjectPeopleOfAllAgesClass ui;
};
