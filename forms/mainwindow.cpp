#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include "global_variate.h"
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
    QString qstr_login_state;
    
    LoginWindow loginw;
    loginw.show();
    this->hide();
    loginw.exec();
    this->show();
    if(User_Manager.islogin())
    {
        qstr_login_state = QString::fromStdString(User_Manager.get_current_user().username);
        ui->LoginRegisterButton->setDisabled(true);
        ui->UserQuitButton->setDisabled(false);
    }
    else
    {
        qstr_login_state = "未登录";
        ui->LoginRegisterButton->setDisabled(false);
        ui->UserQuitButton->setDisabled(true);
    }
    ui -> CurrentUserDisplay -> setText(qstr_login_state);
}

void MainWindow::on_UserQuitButton_clicked()
{

    QMessageBox msgBox(QMessageBox::Information,"退出确认","您确定要退出吗？");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText (QMessageBox::Ok,QString("确 定"));
    msgBox.setButtonText (QMessageBox::Cancel,QString("取 消"));
    msgBox.setDefaultButton(QMessageBox::Ok);
    if(msgBox.exec() == QMessageBox::Ok)
    {
        QString qstr_login_state = "未登录";
        ui -> CurrentUserDisplay -> setText(qstr_login_state);
        ui->LoginRegisterButton->setDisabled(false);
        ui->UserQuitButton->setDisabled(true);

    }
}
