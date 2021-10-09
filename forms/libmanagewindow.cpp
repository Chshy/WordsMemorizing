#include "libmanagewindow.h"
#include "ui_libmanagewindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QListWidgetItem>
#include "class_def/vocabulary.h"
#include "global_variate.h"


LibManageWindow::LibManageWindow(QWidget *parent) : QMainWindow(parent),
                                                    ui(new Ui::LibManageWindow)
{
    ui->setupUi(this);
    ui->FileDisplayLineEdit->setText(QString::fromStdString(Lib_Manager.set_filename));
    for (std::vector<Vocabulary>::size_type it = 0; it < Lib_Manager.list.size(); ++it)
    {
        ui->WordListWidget->addItem(QString::fromStdString(Lib_Manager.list[it].word));
    }
}

LibManageWindow::~LibManageWindow()
{
    delete ui;
}

void LibManageWindow::on_AddWordButton_clicked()
{
    bool word_input;
    QString input_text = QInputDialog::getText(this, tr("单词输入"), tr("请输入单词"), QLineEdit::Normal, 0, &word_input);
    if (word_input && !input_text.isEmpty())
    {
        ui->WordListWidget->addItem(input_text);
        Vocabulary tmp(input_text.toStdString());
        Lib_Manager.add(tmp);
    }
}

void LibManageWindow::on_DeletWordButton_clicked()
{
    int selected = ui->WordListWidget->currentRow();
    if (selected >= 0)
    {
        Lib_Manager.find_and_delet((ui->WordListWidget->item(selected)->text()).toStdString());
        ui->WordListWidget->takeItem(selected);
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "您没有选择单词！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}

void LibManageWindow::on_EditWordButton_clicked()
{

    int selected = ui->WordListWidget->currentRow();
    if (selected >= 0)
    {
        //清空旧列表
        while (ui->ParapListWidget->count())
        {
            ui->ParapListWidget->takeItem(0);
        }
        Lib_Manager.current_edit_ind = Lib_Manager.find((ui->WordListWidget->item(selected)->text()).toStdString());
        for (std::vector<Paraphrase>::size_type it = 0; it < Lib_Manager.list[Lib_Manager.current_edit_ind].paraphrases.size(); ++it)
        {
            ui->ParapListWidget->addItem(QString::fromStdString(Lib_Manager.list[Lib_Manager.current_edit_ind].paraphrases[it].get_display_str()));
        }
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "您没有选择单词！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}

void LibManageWindow::on_AddParapButton_clicked()
{
    if (ui->WordListWidget->currentRow() < 0)
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "您没有选择单词！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if (ui->ParapLineEdit->text() == "")
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "您没有输入中文解释！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QString input_text;
        input_text = ui->CharComboBox->currentText() + " " + ui->ParapLineEdit->text();
        ui->ParapListWidget->addItem(input_text);
        Paraphrase tmp(Paraphrase::WordCharacteristic(ui->CharComboBox->currentIndex()), (ui->ParapLineEdit->text()).toStdString());
        Lib_Manager.list[Lib_Manager.current_edit_ind].add_paraphrase(tmp);
    }
}

void LibManageWindow::on_DeletParapButton_clicked()
{

    if (ui->WordListWidget->currentRow() < 0)
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "您没有选择单词！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    int selected = ui->ParapListWidget->currentRow();

    if (selected >= 0)
    {
        QString qtmp = ui->ParapListWidget->currentItem()->text();
        std::string tmp = qtmp.toStdString();
        Lib_Manager.list[Lib_Manager.current_edit_ind].find_and_delet(tmp);
        ui->ParapListWidget->takeItem(selected);
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "您没有选择词义！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}

void LibManageWindow::on_EditParapButton_clicked()
{
    if (ui->WordListWidget->currentRow() < 0)
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "您没有选择单词！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if (ui->ParapLineEdit->text() == "")
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "您没有输入中文解释！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        int selected = ui->ParapListWidget->currentRow();
        if (selected >= 0)
        {
            Lib_Manager.list[Lib_Manager.current_edit_ind].find_and_delet((ui->ParapListWidget->item(selected)->text()).toStdString());
            Paraphrase tmp(Paraphrase::WordCharacteristic(ui->CharComboBox->currentIndex()), (ui->ParapLineEdit->text()).toStdString());
            Lib_Manager.list[Lib_Manager.current_edit_ind].add_paraphrase(tmp);
            QString input_text;
            input_text = ui->CharComboBox->currentText() + " " + ui->ParapLineEdit->text();
            ui->ParapListWidget->insertItem(selected, input_text);
            ui->ParapListWidget->takeItem(selected + 1);
        }
        else
        {
            QMessageBox msgBox(QMessageBox::Warning, "提示", "您没有选择词义！");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
    }
}

void LibManageWindow::on_SaveFileButton_clicked()
{
    bool save_success = Lib_Manager.savefile(Lib_Manager.set_filename);
    if (save_success)
    {
        QMessageBox msgBox(QMessageBox::Information, "提示", "保存成功");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox(QMessageBox::Warning, "提示", "保存失败");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, QString("确 定"));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}
