#include "testprocesswindow.h"
#include "ui_testprocesswindow.h"

TestProcessWindow::TestProcessWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestProcessWindow)
{
    ui->setupUi(this);
}

TestProcessWindow::~TestProcessWindow()
{
    delete ui;
}
