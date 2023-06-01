#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QDialog>

#include <QWidget>
#include <QVector>
#include "qcustomplot.h"
#include "mainwindow.h"

class Graphics : public QWidget
{
    Q_OBJECT

public:
    Graphics(QWidget *parent = nullptr);
    Graphics(QVector<int>, QVector<int>, QWidget *parent = nullptr);
    ~Graphics();
    QVector<int> stavkaP;
    QVector<int> stavkaD;
    QVector<int> programmerSalaryData;
    QVector<int> designerSalaryData;
    void print();
    void updateGraphs(QVector<int> x, QVector<int>y);
private:
    QCustomPlot *customPlot;
    QCPGraph *programmerSalaryGraph;
    QCPGraph *designerSalaryGraph;
    QCPGraph *monthGraph;
};

#endif // GRAPHICS_H
