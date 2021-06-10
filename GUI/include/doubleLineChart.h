#ifndef DOUBLELINECHART_H
#define DOUBLELINECHART_H

#include "include/basicChart.h"
#include <QtCharts/QChart>
#include <QtCore/QTimer>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class doubleLineChart:public QChart
{
    Q_OBJECT
public:
    doubleLineChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    virtual ~doubleLineChart();

public slots:
    //void handleTimeout();
    void appendSeries(double y, double y_zad);

private:
    //QTimer m_timer;
    QLineSeries *m_series;
    QLineSeries *m2_series;
    QStringList m_titles;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    int length;
    qreal m_step;
    qreal m_x;
    qreal m_y;
};

#endif // DOUBLELINECHART_H

