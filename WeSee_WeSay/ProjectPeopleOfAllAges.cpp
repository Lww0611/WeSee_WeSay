#include "ProjectPeopleOfAllAges.h"
#include <QTableWidget.h>
ProjectPeopleOfAllAges::ProjectPeopleOfAllAges(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    initConnect();
    ui.stackedWidget->setCurrentIndex(0);
    this->setWindowTitle(QStringLiteral("历代人物"));
    data=new DataControl;

    //测试
//    PeoPleBaseInfo info;
//    info.Name = QStringLiteral("李白");
//    info.PersonID = QStringLiteral("32540");
//    info.Alias = QStringLiteral("李拾遗，李翰林，李谪仙，李青莲 太白 酒仙翁，青莲居士 李十二");
//    info.Birth = QStringLiteral("周 长安 元年(701)");
//    info.DeathDays = QStringLiteral("唐 宝应 元年(762)");
////    info.NativePlace = QStringLiteral("任城");
//    info.DieAtTheAge= QStringLiteral("701");
////    info.Krorimaki = QStringLiteral("陇西");
//    setBaseInfo(info);

//    LIST_Alias infoList;
//    AliasList alias, alias1, alias2;
//    alias.Name = "1";
//    alias1.Name = "22";
//    alias2.Name = "333";
//    infoList.push_back(alias);
//    infoList.push_back(alias1);
//    infoList.push_back(alias2);
//    setAliasList(infoList);

//    QStringList list1;
//    list1 << QStringLiteral("李商隐") << QStringLiteral("白居易") << QStringLiteral("李商隐") << QStringLiteral("李商隐") << QStringLiteral("李商隐") << QStringLiteral("李商隐") << QStringLiteral("李商隐") << QStringLiteral("李商隐") << QStringLiteral("李商隐") << QStringLiteral("李商隐");
//    setKindship(list1);
}

ProjectPeopleOfAllAges::~ProjectPeopleOfAllAges()
{}

void ProjectPeopleOfAllAges::showPersonInfo(QString name)
{
    setBaseInfo(*(data->getBaseInfo(name)));
}

void ProjectPeopleOfAllAges::initConnect()
{
    connect(ui.pushButton_form, SIGNAL(clicked()), this, SLOT(SignalPushButton_form()));
    connect(ui.pushButton_relation, SIGNAL(clicked()), this, SLOT(SignalpushButton_relation()));
    connect(ui.checkBox, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_2, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_3, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_4, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_5, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_6, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_7, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_8, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_9, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_10, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_11, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_12, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_13, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_14, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
    connect(ui.checkBox_15, SIGNAL(stateChanged(int)), this, SLOT(SignalStateChanged(int)));
}
void ProjectPeopleOfAllAges::SignalPushButton_form()
{
    ui.stackedWidget->setCurrentIndex(0);
}
void ProjectPeopleOfAllAges::SignalpushButton_relation()
{
    ui.stackedWidget->setCurrentIndex(1);
}
void ProjectPeopleOfAllAges::SignalStateChanged(int index)
{
    QString objName = QObject::sender()->objectName();
    if(objName == "checkBox")
    {
        setTableWidgetVisbal(ui.tableWidget, index);
    }
    else if (objName == "checkBox_2")
    {
        setTableWidgetVisbal(ui.tableWidget_2, index);
    }
    else if (objName == "checkBox_3")
    {
        setTableWidgetVisbal(ui.tableWidget_3, index);
    }
    else if (objName == "checkBox_4")
    {
        setTableWidgetVisbal(ui.tableWidget_4, index);
    }
    else if (objName == "checkBox_5")
    {
        setTableWidgetVisbal(ui.tableWidget_5, index);
    }
    else if (objName == "checkBox_6")
    {
        setTableWidgetVisbal(ui.tableWidget_6, index);
    }
    else if (objName == "checkBox_7")
    {
        setTableWidgetVisbal(ui.tableWidget_7, index);
    }
    else if (objName == "checkBox_8")
    {
        setTableWidgetVisbal(ui.tableWidget_8, index);
    }
    else if (objName == "checkBox_9")
    {
        setTableWidgetVisbal(ui.tableWidget_9, index);
    }
    else if (objName == "checkBox_10")
    {
        setTableWidgetVisbal(ui.widget, index);
    }
    else if (objName == "checkBox_11")
    {
        setTableWidgetVisbal(ui.widget_2, index);
    }
    else if (objName == "checkBox_12")
    {
        setTableWidgetVisbal(ui.widget_3, index);
    }
    else if (objName == "checkBox_13")
    {
        setTableWidgetVisbal(ui.widget_4, index);
    }
    else if (objName == "checkBox_14")
    {
        setTableWidgetVisbal(ui.widget_5, index);
    }
    else if (objName == "checkBox_15")
    {
        setTableWidgetVisbal(ui.widget_6, index);
    }
}
void ProjectPeopleOfAllAges::setTableWidgetVisbal(QTableWidget* table,int index)
{
    if (index == 0)
    {
        table->setVisible(false);
    }
    else
    {
        table->setVisible(true);
    }
}
void ProjectPeopleOfAllAges::setTableWidgetVisbal(QWidget* table, int index)
{
    if (index == 0)
    {
        table->setVisible(false);
    }
    else
    {
        table->setVisible(true);
    }
}
void  ProjectPeopleOfAllAges::setBaseInfo(const PeoPleBaseInfo& info)
{
    ui.label->setText(info.Name);
    ui.label_4->setText(info.PersonID);
    ui.label_17->setText(info.Birth);
    ui.label_6->setText(info.NaImputedBirth);
    ui.label_19->setText(info.DeathDays);
    ui.label_11->setText(info.Sex);
    ui.label_18->setText(info.DieAtTheAge);
    ui.label_12->setText(info.Time);
//    ui.label_20->setText(info.NativePlace);
    ui.label_15->setText(info.Alias);
//    ui.label_21->setText(info.Krorimaki);

    ui.label->setToolTip(info.Name);
    ui.label_4->setToolTip(info.PersonID);
    ui.label_6->setToolTip(info.NaImputedBirth);
    ui.label_17->setToolTip(info.Birth);
    ui.label_19->setToolTip(info.DeathDays);
    ui.label_11->setToolTip(info.Sex);
    ui.label_18->setToolTip(info.DieAtTheAge);
    ui.label_12->setToolTip(info.Time);
//    ui.label_20->setToolTip(info.NativePlace);
    ui.label_15->setToolTip(info.Alias);
//    ui.label_21->setToolTip(info.Krorimaki);
}
void ProjectPeopleOfAllAges::setAliasList(const LIST_Alias& info)
{
    ui.tableWidget->setRowCount(0);
    for (auto &a : info)
    {
        int row = ui.tableWidget->rowCount();
        ui.tableWidget->insertRow(row);

        QTableWidgetItem*item = new QTableWidgetItem();
        item->setText(a.Number);
        ui.tableWidget->setItem(row, 0, item);

        QTableWidgetItem*item1 = new QTableWidgetItem();
        item1->setText(a.Type);
        ui.tableWidget->setItem(row, 1, item1);

        QTableWidgetItem*item2 = new QTableWidgetItem();
        item2->setText(a.Name);
        ui.tableWidget->setItem(row, 2, item2);

        QTableWidgetItem*item3 = new QTableWidgetItem();
        item3->setText(a.Comment);
        ui.tableWidget->setItem(row, 3, item3);
    }
}
void ProjectPeopleOfAllAges::setAddressList(const LIST_AddressList& info)
{
    ui.tableWidget_2->setRowCount(0);
    for (auto &a : info)
    {
        int row = ui.tableWidget_2->rowCount();
        ui.tableWidget_2->insertRow(row);

        QTableWidgetItem*item = new QTableWidgetItem();
        item->setText(a.Number);
        ui.tableWidget_2->setItem(row, 0, item);

        QTableWidgetItem*item1 = new QTableWidgetItem();
        item1->setText(a.Type);
        ui.tableWidget_2->setItem(row, 1, item1);

        QTableWidgetItem*item2 = new QTableWidgetItem();
        item2->setText(a.Nmae);
        ui.tableWidget_2->setItem(row, 2, item2);

        QTableWidgetItem*item3 = new QTableWidgetItem();
        item3->setText(a.Birth);
        ui.tableWidget_2->setItem(row, 3, item3);

        QTableWidgetItem*item4 = new QTableWidgetItem();
        item4->setText(a.DeathDays);
        ui.tableWidget_2->setItem(row, 4, item4);
    }
}
void ProjectPeopleOfAllAges::setOfficialList(const LIST_OfficialList& info)
{
    ui.tableWidget_3->setRowCount(0);
    for (auto &a : info)
    {
        int row = ui.tableWidget_3->rowCount();
        ui.tableWidget_3->insertRow(row);

        QTableWidgetItem*item = new QTableWidgetItem();
        item->setText(a.Number);
        ui.tableWidget_3->setItem(row, 0, item);

        QTableWidgetItem*item1 = new QTableWidgetItem();
        item1->setText(a.OfficialDoor);
        ui.tableWidget_3->setItem(row, 1, item1);

        QTableWidgetItem*item2 = new QTableWidgetItem();
        item2->setText(a.OfficialDiff);
        ui.tableWidget_3->setItem(row, 2, item2);

        QTableWidgetItem*item3 = new QTableWidgetItem();
        item3->setText(a.OfficialAddress);
        ui.tableWidget_3->setItem(row, 3, item3);

        QTableWidgetItem*item4 = new QTableWidgetItem();
        item4->setText(a.Comment);
        ui.tableWidget_3->setItem(row, 4, item4);
    }
}
void ProjectPeopleOfAllAges::setListOfOfficals(const LIST_ListOfOfficals& info)
{
    ui.tableWidget_4->setRowCount(0);
    for (auto &a : info)
    {
        int row = ui.tableWidget_4->rowCount();
        ui.tableWidget_4->insertRow(row);

        QTableWidgetItem*item = new QTableWidgetItem();
        item->setText(a.Number);
        ui.tableWidget_4->setItem(row, 0, item);

        QTableWidgetItem*item1 = new QTableWidgetItem();
        item1->setText(a.DisgrantClass);
        ui.tableWidget_4->setItem(row, 1, item1);

        QTableWidgetItem*item2 = new QTableWidgetItem();
        item2->setText(a.OfficialName);
        ui.tableWidget_4->setItem(row, 2, item2);

        QTableWidgetItem*item3 = new QTableWidgetItem();
        item3->setText(a.OfficialAddress);
        ui.tableWidget_4->setItem(row, 3, item3);

        QTableWidgetItem*item4 = new QTableWidgetItem();
        item4->setText(a.OfficialTime);
        ui.tableWidget_4->setItem(row, 4, item4);

        QTableWidgetItem*item5 = new QTableWidgetItem();
        item5->setText(a.Address);
        ui.tableWidget_4->setItem(row, 5, item5);

        QTableWidgetItem*item6 = new QTableWidgetItem();
        item6->setText(a.Comment);
        ui.tableWidget_4->setItem(row, 6, item6);
    }
}
void ProjectPeopleOfAllAges::setDivisSocial(const LIST_DivisSocial& info)
{
    ui.tableWidget_5->setRowCount(0);
    for (auto &a : info)
    {
        int row = ui.tableWidget_5->rowCount();
        ui.tableWidget_5->insertRow(row);

        QTableWidgetItem*item = new QTableWidgetItem();
        item->setText(a.Number);
        ui.tableWidget_5->setItem(row, 0, item);

        QTableWidgetItem*item1 = new QTableWidgetItem();
        item1->setText(a.SocialDivis);
        ui.tableWidget_5->setItem(row, 1, item1);

        QTableWidgetItem*item2 = new QTableWidgetItem();
        item2->setText(a.Time);
        ui.tableWidget_5->setItem(row, 2, item2);

        QTableWidgetItem*item3 = new QTableWidgetItem();
        item3->setText(a.Address);
        ui.tableWidget_5->setItem(row, 3, item3);

        QTableWidgetItem*item4 = new QTableWidgetItem();
        item4->setText(a.Comment);
        ui.tableWidget_5->setItem(row, 4, item4);
    }
}
void ProjectPeopleOfAllAges::setFamillyRelation(const LIST_FamillyRelation& info)
{
    ui.tableWidget_6->setRowCount(0);
    for (auto &a : info)
    {
        int row = ui.tableWidget_6->rowCount();
        ui.tableWidget_6->insertRow(row);

        QTableWidgetItem*item = new QTableWidgetItem();
        item->setText(a.Number);
        ui.tableWidget_6->setItem(row, 0, item);

        QTableWidgetItem*item1 = new QTableWidgetItem();
        item1->setText(a.Relation);
        ui.tableWidget_6->setItem(row, 1, item1);

        QTableWidgetItem*item2 = new QTableWidgetItem();
        item2->setText(a.RelationPerson);
        ui.tableWidget_6->setItem(row, 2, item2);

        QTableWidgetItem*item3 = new QTableWidgetItem();
        item3->setText(a.Address);
        ui.tableWidget_6->setItem(row, 3, item3);

        QTableWidgetItem*item4 = new QTableWidgetItem();
        item4->setText(a.Comment);
        ui.tableWidget_6->setItem(row, 4, item4);
    }
}
void ProjectPeopleOfAllAges::setSocialRelation(const LIST_SocialRelation& info)
{
    ui.tableWidget_7->setRowCount(0);
    for (auto &a : info)
    {
        int row = ui.tableWidget_7->rowCount();
        ui.tableWidget_7->insertRow(row);

        QTableWidgetItem*item = new QTableWidgetItem();
        item->setText(a.Number);
        ui.tableWidget_7->setItem(row, 0, item);

        QTableWidgetItem*item1 = new QTableWidgetItem();
        item1->setText(a.Relation);
        ui.tableWidget_7->setItem(row, 1, item1);

        QTableWidgetItem*item2 = new QTableWidgetItem();
        item2->setText(a.RelationPerson);
        ui.tableWidget_7->setItem(row, 2, item2);

        QTableWidgetItem*item3 = new QTableWidgetItem();
        item3->setText(a.Address);
        ui.tableWidget_7->setItem(row, 3, item3);

        QTableWidgetItem*item4 = new QTableWidgetItem();
        item4->setText(a.Comment);
        ui.tableWidget_7->setItem(row, 4, item4);
    }
}
void ProjectPeopleOfAllAges::setZhuShu(const LIST_ZhuShu& info)
{
    ui.tableWidget_8->setRowCount(0);
    for (auto &a : info)
    {
        int row = ui.tableWidget_8->rowCount();
        ui.tableWidget_8->insertRow(row);

        QTableWidgetItem*item = new QTableWidgetItem();
        item->setText(a.Number);
        ui.tableWidget_8->setItem(row, 0, item);

        QTableWidgetItem*item1 = new QTableWidgetItem();
        item1->setText(a.Production);
        ui.tableWidget_8->setItem(row, 1, item1);

        QTableWidgetItem*item2 = new QTableWidgetItem();
        item2->setText(a.ProductionTime);
        ui.tableWidget_8->setItem(row, 2, item2);

        QTableWidgetItem*item3 = new QTableWidgetItem();
        item3->setText(a.Role);
        ui.tableWidget_8->setItem(row, 3, item3);

        QTableWidgetItem*item4 = new QTableWidgetItem();
        item4->setText(a.Comment);
        ui.tableWidget_8->setItem(row, 4, item4);
    }
}
void ProjectPeopleOfAllAges::setProvenance(const LIST_Provenance& info)
{
    ui.tableWidget_9->setRowCount(0);
    for (auto &a : info)
    {
        int row = ui.tableWidget_9->rowCount();
        ui.tableWidget_9->insertRow(row);

        QTableWidgetItem*item = new QTableWidgetItem();
        item->setText(a.Number);
        ui.tableWidget_9->setItem(row, 0, item);

        QTableWidgetItem*item1 = new QTableWidgetItem();
        item1->setText(a.Provenance_);
        ui.tableWidget_9->setItem(row, 1, item1);

        QTableWidgetItem*item2 = new QTableWidgetItem();
        item2->setText(a.Comment);
        ui.tableWidget_9->setItem(row, 2, item2);
    }
}
void  ProjectPeopleOfAllAges::setKindship(QStringList& info)
{
    int cloumn = 0;
    int row = 0;
    for (auto& a : info)
    {
        QPushButton*button = new QPushButton(a);
        button->setFixedSize(150, 25);
        button->setStyleSheet("QPushButton{border-radius:5px;background:rgb(170, 170, 255);color:red;font-size:15px;}");
    /*	button->setStyleSheet("border-radius:5px ;background - color:rgb(255, 0, 0)");*/
        connect(button, SIGNAL(clicked()), this, SLOT(SignalButtonClick()));
        if (cloumn < MAXLABLECOUNT)
        {
            ui.gridLayout_7->addWidget(button,row, cloumn);
            cloumn++;
        }
        else
        {
            row++;
            cloumn = 0;
        }
    }
}
void  ProjectPeopleOfAllAges::setSocialRelation(QStringList& info)
{

}
void  ProjectPeopleOfAllAges::setAcademicRelation(QStringList& info)
{

}
void  ProjectPeopleOfAllAges::setFriendRelation(QStringList& info)
{

}
void  ProjectPeopleOfAllAges::setBibliographicRelation(QStringList& info)
{

}
void ProjectPeopleOfAllAges::SignalButtonClick()
{
    QPushButton* button = qobject_cast<QPushButton*>(QObject::sender());
    QString name = button->text();
    qDebug()<<"Change to "<<name;
}
