#ifndef SINGLELINECHART_H
#define SINGLELINECHART_H

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

class singleLineChart:public QChart
{
    Q_OBJECT
public:
    singleLineChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    virtual ~singleLineChart();


public slots:
    void appendSeries(double y);



private:
    QLineSeries *m_series;
    QStringList m_titles;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    int length;
    qreal m_step;
    qreal m_x;
    qreal m_y;


};


#endif // SINGLELINECHART_H
