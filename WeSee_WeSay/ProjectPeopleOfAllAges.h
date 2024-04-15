#pragma once

#include <QtWidgets/QWidget>
#include <QDebug>
#include "ui_ProjectPeopleOfAllAges.h"
#include "ProjectPeopleOfAllAgesCommon.h"
#include "Datacontrol.h"
#define MAXLABLECOUNT 6
class QTableWidget;
class ProjectPeopleOfAllAges : public QWidget
{
    Q_OBJECT

public:
    ProjectPeopleOfAllAges(QWidget *parent = nullptr);
    ~ProjectPeopleOfAllAges();

    // 展示人物全部信息
    void showPersonInfo(QString name);
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

    // 基本信息接口
    void setBaseInfo(const PeoPleBaseInfo& info);

    // 表格形式-别名接口
    void setAliasList(const LIST_Alias& info);
    // 表格形式-地址接口
    void setAddressList(const LIST_AddressList& info);
    // 表格形式-入仕接口
    void setOfficialList(const LIST_OfficialList& info);
    // 表格形式-任官接口
    void setListOfOfficals(const LIST_ListOfOfficals& info);
    // 表格形式-社会区分接口
    void setDivisSocial(const LIST_DivisSocial& info);
    // 表格形式-亲属关系接口
    void setFamillyRelation(const LIST_FamillyRelation& info);
    // 表格形式-社会关系接口
    void setSocialRelation(const LIST_SocialRelation& info);
    // 表格形式-著述接口
    void setZhuShu(const LIST_ZhuShu& info);
    // 表格形式-出处接口
    void setProvenance(const LIST_Provenance& info);

    // 关系图形式-亲属关系接口
    void setKindship(QStringList& info);
    // 关系图形式-社会关系（笼统）接口
    void setSocialRelation(QStringList& info);
    // 关系图形式-朋友关系类接口
    void setFriendRelation(QStringList& info);
    // 关系图形式-学术关系类接口
    void setAcademicRelation(QStringList& info);
    // 关系图形是-著述关系类接口
    void setBibliographicRelation(QStringList& info);
private:
    Ui::ProjectPeopleOfAllAgesClass ui;
    DataControl* data;
};
