#include "widget.h"
#include "ui_widget.h"
#include "mainwindow.h"

Widget::Widget(QWidget *parent) :  QWidget(parent), ui(new Ui::Widget)
{
 ui->setupUi(this);
 ui->lineEdit->setFocus();
 //Автозагрузка списка при запуске виджета
 QFile file("data.txt");
 if (file.open(QIODevice::ReadOnly)) {
  QTextStream stream(&file);
  while (!stream.atEnd()) {
   QString s = stream.readLine();
   ui->listWidget->addItem(s.trimmed());
  }
  file.close();
 }
 else {
  //Как добавить элемент-строку:
  ui->listWidget->addItem(QString(tr("Иванов Иван Иванович | 2345 123567")));
  //Как добавить элемент QListWidgetItem:
  QListWidgetItem *item = new QListWidgetItem();
  item->setText(QString(tr("Петров Пётр Петрович | 3214 654321")));
  item->setToolTip(QString(tr("Подсказка")));
  ui->listWidget->addItem(item);
 }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event) {
 //Автосохранение списка при выходе - событие closeEvent
 int size=ui->listWidget->count();
 if (size) {
  QFile file("data.txt");
  if (file.open(QIODevice::WriteOnly)) {
   QTextStream stream(&file);
   for (int i=0; i<size; i++) {
    stream << ui->listWidget->item(i)->text().trimmed().simplified()
           << (i<size-1 ? "\r\n" : "");
   }
   stream.flush(); file.close();
  }
 }
}

void Widget::on_pushButton_clicked() { //Добавить
 QString text = ui->lineEdit->text().trimmed().simplified();
  //Почистить строку от лишних разделителей
 if (text.isEmpty()) return;
 QList <QListWidgetItem *> list0 = //Поискать элемент
  ui->listWidget->findItems(text,Qt::MatchContains|Qt::MatchFixedString);
 if (list0.count()) { //Уже есть такой - заменить элемент
  QListWidgetItem *item=list0.at(0);
  int index = ui->listWidget->row(item);
  ui->listWidget->setCurrentRow(index);
  on_pushButton_2_clicked(); //Удалить старый
  ui->listWidget->insertItem(index,text); //Вставить новый
 }
 else { //Или добавить новый
  ui->listWidget->addItem(text);
 }
 ui->lineEdit->setText("");
 ui->lineEdit->setFocus();
}

void Widget::on_pushButton_2_clicked() { //Удалить
 int row = ui->listWidget->currentRow();
 if (row<0) {
  QMessageBox msgBox;
  msgBox.setText(QString(tr("Удаление элемента")));
  msgBox.setInformativeText(QString(tr("Выберите элемент для удаления")));
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.exec();
  return;
 }
 QListWidgetItem *item =
  ui->listWidget->takeItem(row);
 ui->lineEdit->setText(item->text()); //Скопировать текст удалённого
 ui->listWidget->setCurrentRow(row);
}

void Widget::on_pushButton_3_clicked() { //Поиск
 //Разрешить выделять несколько элементов:
 ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
 this->unselectAll();
 //Поискать text в списке:
 QString text = ui->lineEdit->text().trimmed().simplified();
 if (text.isEmpty()) return;
 QList <QListWidgetItem *> selected =
  ui->listWidget->findItems (text,
   Qt::MatchContains|Qt::MatchFixedString);
 if (selected.count()) { //Найдено
  foreach (QListWidgetItem *item,selected)
   item->setSelected(true); //Выделить найденное
 }
 else { //Не найдено
  QMessageBox msgBox;
  msgBox.setText(QString(tr("Ничего не найдено")));
  msgBox.exec();
 }
}

void Widget::on_pushButton_4_clicked() { //Сортировка
 //ui->listWidget->setSortingEnabled(true);
 static int Order = Qt::DescendingOrder;
 if (Order==Qt::AscendingOrder) {
  Order = Qt::DescendingOrder;
  ui->listWidget->sortItems(Qt::DescendingOrder);
  ui->pushButton_4->setText(QString(tr("Sort(v)")));
 }
 else {
  Order = Qt::AscendingOrder;
  ui->listWidget->sortItems(Qt::AscendingOrder);
  ui->pushButton_4->setText(QString(tr("Sort(^)")));
 }
}

void Widget::on_pushButton_5_clicked() { //Очистить
 QMessageBox msgBox;
 msgBox.setText(QString(tr("Очистка списка")));
 msgBox.setInformativeText(QString(tr("Вы уверены?")));
 msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
 msgBox.setDefaultButton(QMessageBox::Yes);
 if (msgBox.exec()==QMessageBox::Yes)
  ui->listWidget->clear();
}

void Widget::unselectAll () {
 //Снять выделение со всего, что было выделено:
 QList <QListWidgetItem *> items = ui->listWidget->selectedItems();
 foreach (QListWidgetItem *item,items)
  item->setSelected(false);
}

void Widget::on_listWidget_clicked(const QModelIndex &index){
 this->unselectAll();
 ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
 ui->lineEdit->setText( //Получить текущий элемент как строку
  ui->listWidget->currentItem()->text());
}

QString Widget::itemCount()
{
    int number = ui->listWidget->count();
    QString str = QString::number(number);
    return str;
}
