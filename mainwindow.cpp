#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(update_list()));
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("D:\\WeChat Files\\wxid_0rjefjf6r5p22\\FileStorage\\File\\2024-04\\latest.db"); // 替换为您的数据库文件路径
    if (!m_db.open()) {
        qDebug() << "无法打开数据库：" << m_db.lastError().text();
        return;
    }
    else{
        qDebug()<<"未连接";
    }


}

MainWindow::~MainWindow()
{
    delete ui;
    m_db.close();
}

void MainWindow::update_list(){
    ui->listWidget->clear();
    str=ui->lineEdit->text();

    QString queryString = "SELECT * FROM CBDB_NAME_LIST WHERE name LIKE '%" + str + "%'";
    QSqlQuery query;
    if(str!=""){
        if (!query.exec(queryString)) {
            qDebug() <<"执行失败";
            return;
        }

        while (query.next()) {
            QString value = query.value(1).toString();
            // 将结果添加到List Widget中
            ui->listWidget->addItem(value);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->listWidget->clear();
    str=ui->lineEdit->text();

    QString queryString = "SELECT * FROM CBDB_NAME_LIST WHERE name LIKE '%" + str + "%'";
    QSqlQuery query;
    if(str!=""){
        if (!query.exec(queryString)) {
            qDebug() <<"空语句";
            return;
        }

        while (query.next()) {
            QString value = query.value(1).toString();
            // 将结果添加到List Widget中
            ui->listWidget->addItem(value);
        }
    }
}

