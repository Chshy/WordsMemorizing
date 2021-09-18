#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <string>
#include "class_def/user.h"
#include "global_variate.h"
#include "registerwindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QDialog(parent),
                                            ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->LoginExceptionNote->setVisible(false);
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
    ui->LoginExceptionNote->setVisible(false);
    RegisterWindow regw;
    regw.show();
    //    this->hide();
    regw.exec();
    //    this->show();
}

void LoginWindow::on_LoginButton_clicked()
{
    //读取文本框内容
    QString Qusername = ui->UsernameEdit->text();
    QString Qpassword = ui->PasswordEdit->text();
    //格式转换
    std::string username = Qusername.toStdString();
    std::string password = Qpassword.toStdString();

    //创建一个User对象并设置
    User newuser;
    newuser.SetUsername(username);
    newuser.SetPassword(password);

    if (User_Manager.trylogin(newuser))
    {
        ui->LoginExceptionNote->setVisible(false);
        this->close();
    }
    else
    {
        ui->LoginExceptionNote->setVisible(true);
    }
}
