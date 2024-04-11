#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    str=QString("Welcome to send comments");
    ui->plainTextEdit->setPlainText(str);
    ui->plainTextEdit->setReadOnly(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{   if(ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this,"Warning","Input is empty");
    }
    else{
        str+=QString("\nadmin: ")+ui->lineEdit->text();
        ui->plainTextEdit->setPlainText(str);
        ui->lineEdit->clear();
    }


}

