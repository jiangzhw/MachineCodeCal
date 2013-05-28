#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

    QString getWMIHWInfo(int type);

    QString getCPUID1();
    QString getCPUID2();

    QString getHDLogicalID();

    QString getMac();

    QString getCPUManID();

    QString getMachineCode(int type);

    QString calActiveCode(QString machineCode);






private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
