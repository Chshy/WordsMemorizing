#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include "global_variate.h"
#include "loginwindow.h"
#include "libmanagewindow.h"
#include "testprocesswindow.h"

#include <string>
#include <QDebug>
#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //获取当前exe文件路径
    EXE_QPATH = QCoreApplication::applicationDirPath();
    EXE_QPATH = QDir::toNativeSeparators(EXE_QPATH); //斜杠转反斜杠
    EXE_PATH = EXE_QPATH.toStdString();

    //创建一些文件夹
    std::string mkdir_path = "mkdir " + EXE_PATH + "\\voclist";
    system(mkdir_path.c_str());
    mkdir_path = "mkdir " + EXE_PATH + "\\note";
    system(mkdir_path.c_str());
    mkdir_path = "mkdir " + EXE_PATH + "\\report";
    system(mkdir_path.c_str());

    //设定一些文件读写相关代码的工作目录
    User_Manager.set_exe_path(EXE_PATH);
    User_Manager.read_from();

    if(Vocabulary_Counter.readfile(EXE_PATH + "\\report\\save.dat"))
    {//文件读取成功

    }
    else
    {//文件不存在，新建
        Vocabulary_Counter.savefile(EXE_PATH + "\\report\\save.dat");
    }


    // qDebug() << EXE_PATH.c_str() << endl;

    // qDebug() << "ReadFile:" << User_Manager.read_from() << endl;

    set_ui_login_state();
    qDebug() << "MainWindowOver" << endl;
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
    if (is_login) //登录了
    {
        qstr_login_state = QString::fromStdString(User_Manager.get_current_user().get_username());
    }
    else //没登录
    {
        qstr_login_state = "未登录";
    }
    ui->CurrentUserDisplay->setText(qstr_login_state);

    ui->LoginRegisterButton->setDisabled(is_login);

    ui->UserQuitButton->setDisabled(!is_login);
    ui->TodaySignInButton->setDisabled(!is_login);
    ui->UserSettingButton->setDisabled(!is_login);

    ui->NewLibButton->setDisabled(!is_login);
    ui->EditLibButton->setDisabled(!is_login);
    ui->SelectLibButton->setDisabled(!is_login);
    ui->NewNoteButton->setDisabled(!is_login);
    ui->EditNoteButton->setDisabled(!is_login);
    ui->SelectNoteButton->setDisabled(!is_login);
    //ui->StartLearningButton->setDisabled(!is_login);
    ui->StartTestButton->setDisabled(!is_login);

    if (is_login) //登录了
    {
        refresh_user_status();
//        UserData data = User_Manager.get_current_user().data;
//        ui->TotalSigninDisplay->setText(QString::fromStdString(data.get_signin_display_str()));
//        ui->TotalScoreDisplay->setText(QString::fromStdString(data.get_score_display_str()));
//        ui->TotalAccuracyDisplay->setText(QString::fromStdString(data.get_accuracy_display_str()));
    }
    else //没登录
    {
        ui->TotalSigninDisplay->setText("0");
        ui->TotalScoreDisplay->setText("0");
        ui->TotalAccuracyDisplay->setText("00.00%");
    }

    if(is_login)
    {
        if(User_Manager.currentuser_today_firstlogin())
        {
            ui->TodaySignInButton->setDisabled(false);
        }
        else
        {
            ui->TodaySignInButton->setDisabled(true);
        }
    }
}

void MainWindow::refresh_user_status()
{
    UserData data = User_Manager.get_current_user().data;
    ui->TotalSigninDisplay->setText(QString::fromStdString(data.get_signin_display_str()));
    ui->TotalScoreDisplay->setText(QString::fromStdString(data.get_score_display_str()));
    ui->TotalAccuracyDisplay->setText(QString::fromStdString(data.get_accuracy_display_str()));
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

    QMessageBox msgBox(QMessageBox::Information, "退出确认", "您确定要退出吗？");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
    msgBox.setButtonText(QMessageBox::Cancel, QString("取 消"));
    msgBox.setDefaultButton(QMessageBox::Ok);
    if (msgBox.exec() == QMessageBox::Ok)
    {
        User_Manager.logout();
        set_ui_login_state();
    }
}

void MainWindow::on_TodaySignInButton_clicked()
{
    if(User_Manager.islogin() == false)
        return;
    User_Manager.update_currentuser_logindate();
    ui->TodaySignInButton->setDisabled(true);

    refresh_user_status();
//    UserData data = User_Manager.get_current_user().data;
//    ui->TotalSigninDisplay->setText(QString::fromStdString(data.get_signin_display_str()));
////    ui->TotalScoreDisplay->setText(QString::fromStdString(data.get_score_display_str()));
////    ui->TotalAccuracyDisplay->setText(QString::fromStdString(data.get_accuracy_display_str()));

    QMessageBox msgBox(QMessageBox::Information, "提示", "签到完成");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    return;
}

void MainWindow::on_SelectLibButton_clicked()
{
    //    //定义文件对话框类
    //    QFileDialog *fileDialog = new QFileDialog(this);
    //    //定义文件对话框标题
    //    fileDialog->setWindowTitle(QStringLiteral("选中文件"));
    //    //设置默认文件路径
    //    fileDialog->setDirectory(EXE_QPATH + "\\voclist");
    //    //    QStringList filters;
    //    //    filters << "Image files (*.png *.xpm *.jpg)"
    //    //            << "Text files (*.txt)"
    //    //            << "Any files (*)";
    //    //    fileDialog->setNameFilters(filters);
    //    //设置文件过滤器
    //    fileDialog->setNameFilter(tr("File(*.*)"));
    //    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    //    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //    //设置视图模式
    //    // fileDialog->setViewMode(QFileDialog::Detail);
    //    fileDialog->setViewMode(QFileDialog::List);
    //    //打印所有选择的文件的路径
    //    if (fileDialog->exec())
    //    {
    //        qDebug() << fileDialog->selectedFiles()[0];
    //        QString QPATH;
    //        std::string PATH;
    //        QPATH = fileDialog->selectedFiles()[0];
    //        QPATH = QDir::toNativeSeparators(QPATH); //斜杠转反斜杠
    //        PATH = QPATH.toStdString();
    //        Lib_Manager.readfile(PATH);
    //    }




    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选中文件"));
    fileDialog->setDirectory(EXE_QPATH + "\\voclist");
    fileDialog->setNameFilter(tr("File(*.*)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::List);

    if (fileDialog->exec())
    {
        qDebug() << fileDialog->selectedFiles()[0];
        QString QPATH;
        std::string PATH;
        QPATH = fileDialog->selectedFiles()[0];
        QPATH = QDir::toNativeSeparators(QPATH); //斜杠转反斜杠
        ui->LibDisplayLineEdit->setText(QPATH);
    }
}

void MainWindow::on_NewLibButton_clicked()
{
    // //    LibManageWindow libw;
    // ////    libw.setModal(true);
    // //    libw.setWindowModality(Qt::WindowModal);
    // //    //    pMyMainWindow->setWindowModality(Qt::ApplicationModal);

    // //    //关闭后自动释放窗口,不需要自己释放pMyMainWindow
    // //    libw.setAttribute(Qt::WA_DeleteOnClose);
    // //    this->hide();
    // //    libw.show();

    // ////    this->hide();
    // ////    libw.show();
    // //    this->show();

    //     LibManageWindow *libw = new LibManageWindow(this);
    //     libw->setWindowModality(Qt::WindowModal);
    // //    this->hide();
    //     libw->show();
    // //    this->show();

    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("保存文件"));
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);                                   //设置文件对话框为保存模式
    fileDialog->setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks); //只显示文件夹
    fileDialog->setDirectory(EXE_QPATH + "\\voclist");
    fileDialog->setNameFilter(tr("File(*.*)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::List);

    if (fileDialog->exec())
    {
        qDebug() << fileDialog->selectedFiles()[0];
        QString QPATH;
        std::string PATH;
        QPATH = fileDialog->selectedFiles()[0];
        QPATH = QDir::toNativeSeparators(QPATH); //斜杠转反斜杠
        PATH = QPATH.toStdString();

        Lib_Manager.clear();
        Lib_Manager.set_filename = PATH;
        Lib_Manager.savefile(PATH);

        LibManageWindow *libw = new LibManageWindow(this);
        libw->setWindowModality(Qt::WindowModal);
        libw->show();
    }


}

void MainWindow::on_EditLibButton_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选中文件"));
    fileDialog->setDirectory(EXE_QPATH + "\\voclist");
    fileDialog->setNameFilter(tr("File(*.*)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::List);

    if (fileDialog->exec())
    {
        qDebug() << fileDialog->selectedFiles()[0];
        QString QPATH;
        std::string PATH;
        QPATH = fileDialog->selectedFiles()[0];
        QPATH = QDir::toNativeSeparators(QPATH); //斜杠转反斜杠
        PATH = QPATH.toStdString();

        Lib_Manager.clear();
        Lib_Manager.set_filename = PATH;
        Lib_Manager.readfile(PATH);

        LibManageWindow *libw = new LibManageWindow(this);
        libw->setWindowModality(Qt::WindowModal);
        libw->show();
    }
}

void MainWindow::on_EditNoteButton_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选中文件"));
    fileDialog->setDirectory(EXE_QPATH + "\\note");
    fileDialog->setNameFilter(tr("File(*.*)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::List);

    if (fileDialog->exec())
    {
//        qDebug() << fileDialog->selectedFiles()[0];
        QString QPATH;
        std::string PATH;
        QPATH = fileDialog->selectedFiles()[0];
        QPATH = QDir::toNativeSeparators(QPATH); //斜杠转反斜杠
        PATH = QPATH.toStdString();

        Lib_Manager.clear();
        Lib_Manager.set_filename = PATH;
        Lib_Manager.readfile(PATH);

        LibManageWindow *libw = new LibManageWindow(this);
        libw->setWindowModality(Qt::WindowModal);
        libw->show();
    }
}

void MainWindow::on_NewNoteButton_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("保存文件"));
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);                                   //设置文件对话框为保存模式
    fileDialog->setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks); //只显示文件夹
    fileDialog->setDirectory(EXE_QPATH + "\\note");
    fileDialog->setNameFilter(tr("File(*.*)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::List);

    if (fileDialog->exec())
    {
        qDebug() << fileDialog->selectedFiles()[0];
        QString QPATH;
        std::string PATH;
        QPATH = fileDialog->selectedFiles()[0];
        QPATH = QDir::toNativeSeparators(QPATH); //斜杠转反斜杠
        PATH = QPATH.toStdString();

        Lib_Manager.clear();
        Lib_Manager.set_filename = PATH;
        Lib_Manager.savefile(PATH);

        LibManageWindow *libw = new LibManageWindow(this);
        libw->setWindowModality(Qt::WindowModal);
        libw->show();
    }
}

void MainWindow::on_SelectNoteButton_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("选中文件"));
    fileDialog->setDirectory(EXE_QPATH + "\\note");
    fileDialog->setNameFilter(tr("File(*.*)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::List);

    if (fileDialog->exec())
    {
        qDebug() << fileDialog->selectedFiles()[0];
        QString QPATH;
        std::string PATH;
        QPATH = fileDialog->selectedFiles()[0];
        QPATH = QDir::toNativeSeparators(QPATH); //斜杠转反斜杠
        ui->NoteDisplayLineEdit->setText(QPATH);
    }
}

void MainWindow::on_StartTestButton_clicked()
{
    if (ui->LibDisplayLineEdit->text() == "未选择")
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "您没有选择词库！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    bool no_notebook = false;
    if (ui->NoteDisplayLineEdit->text() == "未选择")
    {
        QMessageBox msgBox(QMessageBox::Information, "提示", "您没有选择笔记本，要继续吗？");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setButtonText(QMessageBox::Cancel, QString("取 消"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        if (msgBox.exec() == QMessageBox::Ok)
        {
            no_notebook = true;
        }
        else
        {
            return;
        }
    }


    QString Lib_QPATH,Note_QPATH;
    std::string Lib_PATH,Note_PATH;

    Lib_QPATH = ui->LibDisplayLineEdit->text();
    Lib_PATH = Lib_QPATH.toStdString();
    Lib_Manager.clear();
    Lib_Manager.set_filename = Lib_PATH;
    Lib_Manager.readfile(Lib_PATH);

    if(!no_notebook)
    {
        Note_QPATH = ui->NoteDisplayLineEdit->text();
        Note_PATH = Note_QPATH.toStdString();
        Note_Manager.clear();
        Note_Manager.set_filename = Note_PATH;
        Note_Manager.readfile(Note_PATH);
    }

    TestProcessWindow *testw = new TestProcessWindow(this);
    testw->setWindowModality(Qt::WindowModal);
    testw->setAttribute(Qt::WA_DeleteOnClose);

//    qDebug() << "11111";
    //读取单词列表
    // testw->Test_Process.list = Lib_Manager.list;
    // testw->Test_Process.visited.resize(Lib_Manager.list.size());

    testw->Test_Process.init(Lib_Manager.list,QuizRange(ui->QuizRangeComboBox->currentIndex()));

//qDebug() << "22222";
    //传入选定的两个路径参数
    //setPATH必须在Test_Process.init后面，因为同时需要设置初始界面
    testw->setPATH(no_notebook,Lib_QPATH,Note_QPATH);
//    testw->no_notebook = no_notebook;

//    ui->LoginRegisterButton->setDisabled(is_login);
//qDebug() << "33333";

    testw->Main_Window_Ptr = this;
    testw->show();

}

void MainWindow::on_GenerateVocStatisticsButton_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("保存文件"));
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);                                   //设置文件对话框为保存模式
    fileDialog->setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks); //只显示文件夹
    fileDialog->setDirectory(EXE_QPATH + "\\report");
    fileDialog->setNameFilter(tr("File(*.*)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::List);

    if (fileDialog->exec())
    {
        QString QPATH;
        std::string PATH;
        QPATH = fileDialog->selectedFiles()[0];
        QPATH = QDir::toNativeSeparators(QPATH); //斜杠转反斜杠
        PATH = QPATH.toStdString();

        bool generate_sucess = Vocabulary_Counter.generate(PATH);
        if(generate_sucess)
        {
            QMessageBox msgBox(QMessageBox::Information, "提示", "报告生成完成");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            std::string txt_path = "notepad " + PATH;
            system(txt_path.c_str());
        }
        else
        {
            QMessageBox msgBox(QMessageBox::Warning, "提示", "报告生成错误");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
    }
}

void MainWindow::on_ClearVocStatisticsButton_clicked()
{
    QMessageBox msgBox(QMessageBox::Information, "提示", "您确定要清空统计历史吗？");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
    msgBox.setButtonText(QMessageBox::Cancel, QString("取 消"));
    msgBox.setDefaultButton(QMessageBox::Ok);
    if (msgBox.exec() == QMessageBox::Ok)
    {
        Vocabulary_Counter.clear();
        Vocabulary_Counter.savefile(EXE_PATH + "\\report\\save.dat");
    }
}
