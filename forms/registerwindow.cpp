#include "registerwindow.h"
#include "ui_registerwindow.h"

#include <string>
#include <QMessageBox>
#include "class_def/user.h"
#include "global_variate.h"

RegisterWindow::RegisterWindow(QWidget *parent) : QDialog(parent),
                                                  ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_CancelButton_clicked()
{
    this->close();
}

void RegisterWindow::on_RegisterButton_clicked()
{

    //读取文本框内容
    QString Qusername = ui->UsernameEdit->text();
    QString Qpassword = ui->PasswordEdit->text();
    QString Qpasswordconfirm = ui->PasswordConfirmEdit->text();
    //格式转换
    std::string username = Qusername.toStdString();
    std::string password = Qpassword.toStdString();
    std::string passwordconfirm = Qpasswordconfirm.toStdString();

    //输入合法性检查

    if (password.compare(passwordconfirm) != 0)
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "密码与确认密码不一致！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    //创建一个User对象并设置
    User newuser;
    newuser.SetUsername(username);
    newuser.SetPassword(password);

    if (User_Manager.tryregister(newuser))
    {
        this->close();
    }
}

void RegisterWindow::on_UsernameEdit_editingFinished()
{
}
