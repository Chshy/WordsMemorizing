#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "loginwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LoginRegisterButton_clicked()
{
    LoginWindow loginw;
    loginw.show();
    this->hide();
    loginw.exec();
    this->show();
}
