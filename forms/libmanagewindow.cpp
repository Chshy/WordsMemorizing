#include "libmanagewindow.h"
#include "ui_libmanagewindow.h"

LibManageWindow::LibManageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LibManageWindow)
{
    ui->setupUi(this);
}

LibManageWindow::~LibManageWindow()
{
    delete ui;
}
