#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include "global_variate.h"
#include "loginwindow.h"

#include <string>
#include <QDebug>
#include <QDir>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //获取当前exe文件路径
    EXE_QPATH = QCoreApplication::applicationDirPath();
    EXE_QPATH = QDir::toNativeSeparators(EXE_QPATH);//斜杠转反斜杠
    EXE_PATH = EXE_QPATH.toStdString();
    //设定一些文件读写相关代码的工作目录
    User_Manager.set_exe_path(EXE_PATH);

    qDebug() << EXE_PATH.c_str() << endl;
    
    qDebug() << "ReadFile:" << User_Manager.read_from() << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//登录状态显示切换函数
//2021/09/20
void MainWindow::set_ui_login_state()
{
    bool is_login = User_Manager.islogin();
    QString qstr_login_state;
    if(is_login)//登录了
    {
        qstr_login_state = QString::fromStdString(User_Manager.get_current_user().username);
    }
    else//没登录
    {
        qstr_login_state = "未登录";
        
    }

    ui->LoginRegisterButton->setDisabled(is_login);

    ui->UserQuitButton->setDisabled(!is_login);
    ui->TodaySignInButton->setDisabled(!is_login);
    ui->UserSettingButton->setDisabled(!is_login);







    ui -> CurrentUserDisplay -> setText(qstr_login_state);
    


}

void MainWindow::on_LoginRegisterButton_clicked()
{
    QString qstr_login_state;
    
    LoginWindow loginw;
    loginw.show();
    this->hide();
    loginw.exec();
    this->show();

    set_ui_login_state();
    // if(User_Manager.islogin())
    // {
    //     qstr_login_state = QString::fromStdString(User_Manager.get_current_user().username);
    //     ui->LoginRegisterButton->setDisabled(true);
    //     ui->UserQuitButton->setDisabled(false);
    // }
    // else
    // {
    //     qstr_login_state = "未登录";
    //     ui->LoginRegisterButton->setDisabled(false);
    //     ui->UserQuitButton->setDisabled(true);
    // }
    // ui -> CurrentUserDisplay -> setText(qstr_login_state);
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
        User_Manager.logout();
        set_ui_login_state();
    }
}
