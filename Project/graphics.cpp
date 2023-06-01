#include "graphics.h"
#include "mainwindow.h"
#include "ui_graphics.h"

Graphics::Graphics(QWidget *parent)
    : QWidget(parent)
{

    // Создаем объект QCustomPlot
    customPlot = new QCustomPlot(this);

    // Масштабируем оси графика
    customPlot->rescaleAxes();

    // Устанавливаем минимальный размер графика
    customPlot->setMinimumSize(600, 400);

    // Создаем объект QCPGraph для ставок программистам
    programmerSalaryGraph = customPlot->addGraph();
    // Создаем объект QCPGraph для ставок дизайнерам
    designerSalaryGraph = customPlot->addGraph();
    // Создаем объект QCPGraph для месяцев
    monthGraph = customPlot->addGraph();

    // Заполняем данные для зарплат программистам, дизайнерам и месяцев
    programmerSalaryData = {100,200,300,400,200};
    designerSalaryData = {200,300,100,350,50};
    QVector<int> monthData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // Добавляем данные в QCPGraph
    for (int i = 0; i < programmerSalaryData.size(); ++i) {
        programmerSalaryGraph->addData(monthData[i], programmerSalaryData[i]);
        designerSalaryGraph->addData(monthData[i], designerSalaryData[i]);
    }

    // Устанавливаем заголовок графика
    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, "Stavka of Months"));

    // Устанавливаем оси координат
    customPlot->xAxis->setLabel("Months");
    customPlot->yAxis->setLabel("Stavka");

    // Добавляем легенду
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    customPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    QVector<QString> legendNames {"Programmer Salary", "Designer Salary"};
    programmerSalaryGraph->setName(legendNames[0]);
    designerSalaryGraph->setName(legendNames[1]);

    // Устанавливаем цвета графиков
    programmerSalaryGraph->setPen(QPen(Qt::blue));
    designerSalaryGraph->setPen(QPen(Qt::red));

    // Устанавливаем диапазон значений на осях
    customPlot->xAxis->setRange(0, 12);
    customPlot->yAxis->setRange(50, 350);

    // Отображаем график на экране
    customPlot->replot();
}

Graphics::Graphics(QVector<int> x, QVector<int> y, QWidget *parent) : QWidget(parent)
{
    // Создаем объект QCustomPlot
    customPlot = new QCustomPlot(this);

    // Масштабируем оси графика
    customPlot->rescaleAxes();

    // Устанавливаем минимальный размер графика
    customPlot->setMinimumSize(600, 400);

    // Создаем объект QCPGraph для ставок программистам
    programmerSalaryGraph = customPlot->addGraph();
    // Создаем объект QCPGraph для ставок дизайнерам
    designerSalaryGraph = customPlot->addGraph();
    // Создаем объект QCPGraph для месяцев
    monthGraph = customPlot->addGraph();

    // Заполняем данные для зарплат программистам, дизайнерам и месяцев
    programmerSalaryData = x;
    designerSalaryData = y;
    QVector<int> monthData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // Добавляем данные в QCPGraph
    for (int i = 0; i < programmerSalaryData.size(); ++i) {
        programmerSalaryGraph->addData(monthData[i], programmerSalaryData[i]);
        designerSalaryGraph->addData(monthData[i], designerSalaryData[i]);
    }

    // Устанавливаем заголовок графика
    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, "Stavka of Months"));

    // Устанавливаем оси координат
    customPlot->xAxis->setLabel("Months");
    customPlot->yAxis->setLabel("Stavka");

    // Добавляем легенду
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    customPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    QVector<QString> legendNames {"Programmer Salary", "Designer Salary"};
    programmerSalaryGraph->setName(legendNames[0]);
    designerSalaryGraph->setName(legendNames[1]);

    // Устанавливаем цвета графиков
    programmerSalaryGraph->setPen(QPen(Qt::blue));
    designerSalaryGraph->setPen(QPen(Qt::red));

    // Устанавливаем диапазон значений на осях
    customPlot->xAxis->setRange(0, 12);
    customPlot->yAxis->setRange(100, 300);

    // Отображаем график на экране
    customPlot->replot();
}

Graphics::~Graphics()
{
    delete customPlot;
}
