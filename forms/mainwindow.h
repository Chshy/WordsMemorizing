#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void refresh_user_status();



private slots:
    void on_LoginRegisterButton_clicked();

    void on_UserQuitButton_clicked();

    void on_TodaySignInButton_clicked();

    void on_SelectLibButton_clicked();

    void on_NewLibButton_clicked();

    void on_EditLibButton_clicked();

    void on_EditNoteButton_clicked();

    void on_NewNoteButton_clicked();

    void on_SelectNoteButton_clicked();

    void on_StartTestButton_clicked();

private:
    Ui::MainWindow *ui;
    void set_ui_login_state();
};
#endif // MAINWINDOW_H
