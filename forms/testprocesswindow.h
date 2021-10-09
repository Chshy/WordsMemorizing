#ifndef TESTPROCESSWINDOW_H
#define TESTPROCESSWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include "mainwindow.h"
#include "class_def/testprocess.h"
#include "global_variate.h"

namespace Ui
{
    class TestProcessWindow;
}

class TestProcessWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestProcessWindow(QWidget *parent = nullptr);
    ~TestProcessWindow();

    TestProcess Test_Process;
    bool no_notebook;
    QString Lib_QPATH;
    QString Note_QPATH;

    MainWindow *Main_Window_Ptr;

    void setPATH(bool no_notebook_input, QString Lib_QPATH_input, QString Note_QPATH_input);
    void DrawQuiz();

private slots:
    void on_AnswerButton_clicked();

    void on_NextQuizButton_clicked();

    void on_AddToNoteButton_clicked();

private:
    Ui::TestProcessWindow *ui;

    QuizUnit quiz;
    QButtonGroup *ChoiceSelect;
};

#endif // TESTPROCESSWINDOW_H
