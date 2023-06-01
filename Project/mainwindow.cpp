#include "widget.h"
#include "widget2.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include "auth.h"
#include <QDir>
#include <QTextStream>
#include <QFile>
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file("D:/QuTo/Project/worktime/worktime.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString dateTimeString = currentDateTime.toString(Qt::ISODate);
        out << Auth::UserLogon << " " << dateTimeString << endl;
        file.close();
    }
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_p->hide();
    ui->lineEdit_d->hide();
    ui->label_5->hide();
    ui->ok1->hide();
    ui->ok2->hide();
    ui->label_8->hide();
    stavkaP = 220;
    stavkaD = 198;
    afterbudget = beforebudget = 1000000;
    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr,SIGNAL(timeout()),this,SLOT(updCP()));
    connect(tmr,SIGNAL(timeout()),this,SLOT(updCD()));
    connect(tmr,SIGNAL(timeout()),this,SLOT(updstP()));
    connect(tmr,SIGNAL(timeout()),this,SLOT(updstD()));
    connect(tmr,SIGNAL(timeout()),this,SLOT(updBefB()));
    connect(tmr,SIGNAL(timeout()),this,SLOT(updAftB()));
    tmr->start();
    stavkavP = {};
    stavkavD = {};
}

QString full_info_of_user;
QFile written_requests2("D:/Quto/Project/requests/written_requests.txt");
QFile requests2("D:/QuTo/Project/requests/requests.txt");
QFile userdata("D:/QuTo/Project/userdata/userdata.txt");
QFile file("D:/QuTo/Project/worktime/worktime.txt");

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() // ред. Программисты
{
    Widget2* w2 = new Widget2();
    w2->setWindowTitle("Список сотрудников-программистов");
    w2->setAttribute(Qt::WA_DeleteOnClose);
    w2->show();
}

void MainWindow::on_pushButton_2_clicked() // ред. Дизайнеры
{
    Widget* w = new Widget();
    w->setWindowTitle("Список сотрудников-дизайнеров");
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

void MainWindow::updstP()
{
    ui->stPP->setText(QString::number(stavkaP) + " руб/ час");
}

void MainWindow::updstD()
{
    ui->stDD->setText(QString::number(stavkaD) + " руб/ час");
}

void MainWindow::updCP()
{
    Widget2 w;
    ui->cntP->setText(w.itemCount() + " чел.");
}

void MainWindow::updCD()
{
    Widget w;
    ui->cntD->setText(w.itemCount() + " чел.");
}


int MainWindow::on_zpP_clicked()
{
    Widget2 w2;
    int PayP = 22*8*stavkaP * w2.itemCount().toInt();
    ui->label_p->setText("Общая выплата программистам за текущий месяц\nсоставит: " + QString::number(PayP) + " рублей");
    beforebudget = afterbudget - PayP;
    return PayP;
}


int MainWindow::on_zpD_clicked()
{
    Widget w;
    int PayD = 22 * 8 * stavkaD * w.itemCount().toInt();
    ui->label_p->setText("Общая выплата программистам за текущий месяц\nсоставит: " + QString::number(PayD) + " рублей");
    beforebudget = afterbudget - PayD;
    return PayD;
}

void MainWindow::UserName() {
    if (!userdata.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл userdata.txt");
        return;
    }
    QTextStream in(&userdata);
    in.setCodec("UTF-8");
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(':');
        if (parts.size() == 4) {
            QString storedUsername = parts.at(0);
            if (Auth::UserLogon == storedUsername) {
                QString storedName = parts.at(1);
                QString storedAge = parts.at(2);
                QString storedEdu = parts.at(3);
                userdata.close();
                full_info_of_user = storedName + ", " + storedAge + " лет" + "\n\nОбразование: " + storedEdu;
                return;
            }
        }
    }
}

QString getImagePathByLogin(const QString& login)
{
    QString imagePath;
    QDir imageDir("D:/QuTo/Project/profile_images");
    QStringList fileList = imageDir.entryList(QDir::Files);
    for (const QString& file : fileList) {
        QString fileName = file.section('.', 0, 0);
        if (fileName == login) {
            imagePath = imageDir.absoluteFilePath(file);
            break;
        }
    }

    return imagePath;
}

int MainWindow::on_zpAll_clicked()
{
    int PP = on_zpP_clicked();
    int PD = on_zpD_clicked();
    int PayAll = PP + PD;
    ui->label_p->setText("Общая выплата всем сотрудникам за текущий месяц\nсоставит: " + QString::number(PayAll) + " рублей");
    beforebudget = afterbudget - PayAll;
    return PayAll;
}

void MainWindow::updAftB()
{
    ui->afterPay->setText(QString::number(afterbudget) + " рублей");
}

void MainWindow::updBefB()
{
    ui->beforePay->setText(QString::number(beforebudget) + " рублей");
}

void MainWindow::on_ready_clicked()
{
    afterbudget = beforebudget;
    QMessageBox::information(this,"Готово","Выплата совершена");
}


void MainWindow::on_ok1_clicked()
{
    stavkaP = ui->lineEdit_p->text().toInt();
    stavkavP.push_back(stavkaP);
}


void MainWindow::on_ok2_clicked()
{
    stavkaD = ui->lineEdit_d->text().toInt();
    stavkavD.push_back(stavkaD);
}


void MainWindow::on_action_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->profile_image->setStyleSheet("border-radius:8px; border: 1px solid gray;background-image: url(" + getImagePathByLogin(Auth::UserLogon) + ")");
    UserName();
    ui->user_data->setText(full_info_of_user);
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_pushButton_6_clicked()
{
    Graphics* a = new Graphics(stavkavP,stavkavD);
    a->setWindowTitle("График изменения тарифных ставок");
    a->setAttribute(Qt::WA_DeleteOnClose);
    a->show();
}

