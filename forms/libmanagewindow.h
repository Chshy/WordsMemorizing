#ifndef LIBMANAGEWINDOW_H
#define LIBMANAGEWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class LibManageWindow;
}

class LibManageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LibManageWindow(QWidget *parent = nullptr);
    ~LibManageWindow();

private slots:
    void on_AddWordButton_clicked();

    void on_DeletWordButton_clicked();

    void on_EditWordButton_clicked();

    void on_AddParapButton_clicked();

    void on_DeletParapButton_clicked();

    void on_EditParapButton_clicked();

    void on_SaveFileButton_clicked();

private:
    Ui::LibManageWindow *ui;
};

#endif // LIBMANAGEWINDOW_H
