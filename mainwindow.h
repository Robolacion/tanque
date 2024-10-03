#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<Qtimer>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int k=500;

private:
    Ui::MainWindow *ui;

public slots:

    void tank_flow();
    void Run_or_Stop();
    void set_timer();
    void tank_size();
private slots:

};


#endif // MAINWINDOW_H
