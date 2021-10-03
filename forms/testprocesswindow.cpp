#include "testprocesswindow.h"
#include "ui_testprocesswindow.h"
#include <QMessageBox>
#include <QDebug>

TestProcessWindow::TestProcessWindow(QWidget *parent) : QMainWindow(parent),
                                                        ui(new Ui::TestProcessWindow)
{
    ui->setupUi(this);

    ChoiceSelect=new QButtonGroup(this);
    ChoiceSelect->addButton(ui->radioButton_A,0);
    ChoiceSelect->addButton(ui->radioButton_B,1);
    ChoiceSelect->addButton(ui->radioButton_C,2);
    ChoiceSelect->addButton(ui->radioButton_D,3);
    ui->radioButton_A->setChecked(true); //默认选中A
}

TestProcessWindow::~TestProcessWindow()
{
    delete ui;
}

void TestProcessWindow::setPATH(bool no_notebook_input, QString Lib_QPATH_input, QString Note_QPATH_input)
{
    no_notebook = no_notebook_input;

    Lib_QPATH = Lib_QPATH_input;
    ui->LibDisplayLineEdit->setText(Lib_QPATH);

    if (!no_notebook) //如果有错题本
    {
        Note_QPATH = Note_QPATH_input;
        ui->NoteDisplayLineEdit->setText(Note_QPATH);
        // ui->AddToNoteButton->setDisabled(false);
    }
    else
    {
        ui->NoteDisplayLineEdit->setText("未选择错题本");
        // ui->AddToNoteButton->setDisabled(true);
        
    }

    




    //进度界面初始化
    ui->LibProgressBar->setMaximum(Test_Process.get_quiz_total());
    ui->LibProgressBar->setValue(Test_Process.get_ans_total());
    ui->ProgressDisplay->setText(QString::fromStdString(Test_Process.get_progress_display_str()));
    ui->AccuracyDisplay->setText(QString::fromStdString(Test_Process.get_accuracy_display_str()));

    //初始化第一次出题
    DrawQuiz();

}

void TestProcessWindow::DrawQuiz()
{
    qDebug() << "StartDrawQuiz";
    ui->NextQuizButton->setDisabled(true);
    ui->AnswerButton->setDisabled(false);
    ui->ReslDisplayEdit->clear();
    ui->AddToNoteButton->setDisabled(true);
    
    
    qDebug() << ui->QuizTypeComboBox->currentIndex();
    qDebug() << ui->QuizTypeComboBox->currentText();
    
    
    //出题
    quiz = Test_Process.DrawQuiz(QuizType(ui->QuizTypeComboBox->currentIndex()));
    ui->QuizDisplayEdit->setText(QString::fromStdString(quiz.quiz_str));

    //设置显示
    switch(quiz.type)
    {
    case QUIZTYPE_CHOICE:
        ui->AnswerEdit->setDisabled(true);
        ui->radioButton_A->setDisabled(false);
        ui->radioButton_B->setDisabled(false);
        ui->radioButton_C->setDisabled(false);
        ui->radioButton_D->setDisabled(false);

        break;
    case QUIZTYPE_FILLIN:
        ui->AnswerEdit->setDisabled(false);
        ui->radioButton_A->setDisabled(true);
        ui->radioButton_B->setDisabled(true);
        ui->radioButton_C->setDisabled(true);
        ui->radioButton_D->setDisabled(true);
        break;
    default:
        break;
    }


}

//答题按钮
void TestProcessWindow::on_AnswerButton_clicked()
{
//    switch(ChoiceSelect->checkedId())
//    {
//    case 0:
//        qDebug() <<"A"<<endl;
//        break;
//    case 1:
//        qDebug() <<"B"<<endl;
//        break;
//    case 2:
//        qDebug() <<"C"<<endl;
//        break;
//    case 3:
//        qDebug() <<"D"<<endl;
//        break;
//    default:
//        break;
//    }


    //Disable所有控件
    ui->AnswerEdit->setDisabled(true);
    ui->radioButton_A->setDisabled(true);
    ui->radioButton_B->setDisabled(true);
    ui->radioButton_C->setDisabled(true);
    ui->radioButton_D->setDisabled(true);
    ui->AnswerButton->setDisabled(true);



    bool ans_correct = false;
    std::string display_str = "回答";

    //判断答案正确错误
    switch(quiz.type)
    {
    case QUIZTYPE_CHOICE:
        ans_correct = (QuizChoice(ChoiceSelect->checkedId()) == quiz.ans_choice);
        break;
    case QUIZTYPE_FILLIN:
        {
            QString ans_qtmp = ui->AnswerEdit->text();
            std::string ans_tmp = ans_qtmp.toStdString();
            ans_correct = ((quiz.ans_str.compare(ans_tmp)) == 0);
        }
        break;
    default:
        break;
    }

    display_str += (ans_correct)?("正确\n"):("错误\n");
    display_str += "正确答案为:\n";

    switch(quiz.type)
    {
    case QUIZTYPE_CHOICE:
        {
            switch(quiz.ans_choice)
            {
            case QUIZCHOICE_A:
                display_str += "A";
                break;
            case QUIZCHOICE_B:
                display_str += "B";
                break;
            case QUIZCHOICE_C:
                display_str += "C";
                break;
            case QUIZCHOICE_D:
                display_str += "D";
                break;
            default:
                break;
            }

        }
        break;
    case QUIZTYPE_FILLIN:
        display_str += quiz.ans_str;
        break;
    default:
        break;
    }
    display_str += "\n";

    //显示正确答案
    ui->ReslDisplayEdit->setText(QString::fromStdString(display_str));

    //更新数据
    Test_Process.DataUpdate(ans_correct);

    ui->LibProgressBar->setValue(Test_Process.get_ans_total());
    ui->ProgressDisplay->setText(QString::fromStdString(Test_Process.get_progress_display_str()));
    ui->AccuracyDisplay->setText(QString::fromStdString(Test_Process.get_accuracy_display_str()));

    ui->AddToNoteButton->setDisabled(no_notebook);

    if(Test_Process.get_ans_total() >= Test_Process.get_quiz_total())
    {//如果题目回答完了
        // QMessageBox msgBox(QMessageBox::Information, "提示", "已完成词库内所有单词");
        // msgBox.setStandardButtons(QMessageBox::Ok);
        // msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        // msgBox.setDefaultButton(QMessageBox::Ok);
        // msgBox.exec();
        // return;
        QMessageBox msgBox(QMessageBox::Information, "提示", "已完成词库内所有单词，是否返回主界面？");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setButtonText(QMessageBox::Cancel, QString("取 消"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        if (msgBox.exec() == QMessageBox::Ok)
        {
            this->close();
        }
    }
    else
    {
        ui->NextQuizButton->setDisabled(false);
    } 
}

void TestProcessWindow::on_NextQuizButton_clicked()
{
    DrawQuiz();
}

void TestProcessWindow::on_AddToNoteButton_clicked()
{
    Note_Manager.add(quiz.voc);
    Note_Manager.savefile(Note_QPATH.toStdString());
    ui->AddToNoteButton->setDisabled(true);
}
