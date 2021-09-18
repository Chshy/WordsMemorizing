#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "registerwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_CancelButton_clicked()
{
    this->close();
}

void LoginWindow::on_RegisterButton_clicked()
{
    RegisterWindow regw;
    regw.show();
//    this->hide();
    regw.exec();
//    this->show();
}
