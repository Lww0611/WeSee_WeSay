#include "kinghistory.h"
#include "mainscreen.h"
#include "historytoday.h"
#include "ProjectPeopleOfAllAges.h"

KingHistory::KingHistory(QWidget *parent) : QWidget(parent) {
    setWindowTitle("King's History");
    setFixedSize(1500, 1000);

    // 设置背景图片
    QPixmap backgroundPixmap("D:/Desktop/history/history/picture/background.jpg");
    backgroundPixmap = backgroundPixmap.scaled(size()); // 缩放背景图片以适应窗口大小
    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(backgroundPixmap);
    backgroundLabel->setGeometry(0, 0, width(), height()); // 设置背景标签大小与窗口一致

    // 创建按钮
    QPushButton *buttonHistoryDynasty = new QPushButton("历史朝代表", this);
    QPushButton *buttontoday = new QPushButton("历史上的今天", this);
    QPushButton *buttonRelationGraph = new QPushButton("人物关系图", this);


    // 设置按钮样式
    QString buttonStyle = "QPushButton {"
                          "   background-color: white;"
                          "   color: black;"
                          "   border: 1px solid black;"
                          "   border-radius: 10px;" // 调整按钮圆角半径
                          "   padding: 10px 20px;" // 调整按钮内边距
                          "}"
                          "QPushButton:hover {"
                          "   background-color: lightgray;"
                          "}";
    buttonHistoryDynasty->setStyleSheet(buttonStyle);
    buttontoday->setStyleSheet(buttonStyle);
    buttonRelationGraph->setStyleSheet(buttonStyle);


    // 设置按钮大小
    QSize buttonSize(200, 60); // 调整按钮大小
    buttonHistoryDynasty->setFixedSize(buttonSize);
    buttontoday->setFixedSize(buttonSize);
    buttonRelationGraph->setFixedSize(buttonSize);

    // 设置按钮点击事件
    connect(buttonHistoryDynasty, &QPushButton::clicked, this, &KingHistory::openHistoryDynastyPage);
    connect(buttontoday, &QPushButton::clicked, this, &KingHistory::openhistorytoday);
    connect(buttonRelationGraph, &QPushButton::clicked, this, &KingHistory::openRelationGraphPage);

    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(buttonHistoryDynasty);
    layout->addWidget(buttontoday);
    layout->addWidget(buttonRelationGraph);

    layout->setAlignment(Qt::AlignCenter);

    setLayout(layout);
}

void KingHistory::openHistoryDynastyPage() {
    // 创建并显示历史朝代表页面
    MainScreen *page = new MainScreen;
    page->show();
}

void KingHistory::openRelationGraphPage() {
    // 创建并显示人物关系图页面
    ProjectPeopleOfAllAges *w =new ProjectPeopleOfAllAges;
    w->show();
}

void KingHistory::openhistorytoday() {
    // 创建并显示历史上的今天
    HistoryToday *historytoday =new HistoryToday;
    historytoday->show();
}
