#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget> /* необходимые библиотеки */
#include <QtWidgets>
#include <QEvent>
#include <QTextStream>
#include <QString>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString itemCount();
private slots:
    void on_listWidget_clicked(const QModelIndex &index);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void closeEvent(QCloseEvent *); /* обработчик закрытия окна */
private:
    Ui::Widget *ui;
    void unselectAll (); /* метод для снятия выделения с элементов */
};

#endif // WIDGET_H
