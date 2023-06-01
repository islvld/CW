#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include "graphics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int stavkaP;
    int stavkaD;
    int beforebudget;
    int afterbudget;
    QVector<int> stavkavP;
    QVector<int> stavkavD;
    void UserName();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void updCP();
    void updCD();
    void updstP();
    void updstD();
    void updBefB();
    void updAftB();
    int on_zpP_clicked();
    int on_zpD_clicked();
    int on_zpAll_clicked();

    void on_ready_clicked();

    void on_ok1_clicked();

    void on_ok2_clicked();

    void on_action_triggered();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* tmr;
};
#endif // MAINWINDOW_H
