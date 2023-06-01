#ifndef WIDGET2_H
#define WIDGET2_H

#include <QWidget> /* необходимые библиотеки */
#include <QtWidgets>
#include <QEvent>
#include <QTextStream>
#include <QString>

namespace Ui {
class Widget2;
}

class Widget2 : public QWidget
{
    Q_OBJECT

public:
    explicit Widget2(QWidget *parent = 0);
    ~Widget2();
    QString itemCount();
private slots:
    void on_listWidget_clicked(const QModelIndex &index);
    void on_pushButton_8_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_4_clicked();
    void closeEvent(QCloseEvent *); /* обработчик закрытия окна */
private:
    Ui::Widget2 *ui;
    void unselectAll (); /* метод для снятия выделения с элементов */
};

#endif // WIDGET_H
