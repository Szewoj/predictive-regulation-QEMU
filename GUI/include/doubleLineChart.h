#ifndef DOUBLELINECHART_H
#define DOUBLELINECHART_H

#include <QtCharts/QChart>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QDebug>

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
    void appendSeries(double y, double y_zad);

private:
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

