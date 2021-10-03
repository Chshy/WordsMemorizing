#ifndef LIBMANAGEWINDOW_H
#define LIBMANAGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class LibManageWindow;
}

class LibManageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LibManageWindow(QWidget *parent = nullptr);
    ~LibManageWindow();

private:
    Ui::LibManageWindow *ui;
};

#endif // LIBMANAGEWINDOW_H
