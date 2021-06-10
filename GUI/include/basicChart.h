#ifndef BASICCHART_H
#define BASICCHART_H

#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

class basicChart: public QChart
{
    Q_OBJECT
public:
    basicChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    virtual ~basicChart();
};


#endif // BASICCHART_H

