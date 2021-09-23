#ifndef TESTPROCESSWINDOW_H
#define TESTPROCESSWINDOW_H

#include <QMainWindow>

namespace Ui {
class TestProcessWindow;
}

class TestProcessWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestProcessWindow(QWidget *parent = nullptr);
    ~TestProcessWindow();

private:
    Ui::TestProcessWindow *ui;
};

#endif // TESTPROCESSWINDOW_H
