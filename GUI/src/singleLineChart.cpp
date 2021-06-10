#include "include/singleLineChart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <QDebug>

singleLineChart::singleLineChart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
    length(0),
    m_step(0),
    m_x(0),
    m_y(0)
{
        m_series = new QLineSeries(this);
        QPen pen(Qt::red);
        pen.setWidth(3);
        m_series->setPen(pen);
        m_series->append(0, 0);

        addSeries(m_series);

        m_axisX->setLabelFormat("%.0f");
        addAxis(m_axisX,Qt::AlignBottom);
        addAxis(m_axisY,Qt::AlignLeft);
        m_series->attachAxis(m_axisX);
        m_series->attachAxis(m_axisY);

        m_axisX->setTickCount(13);
        m_axisX->setTickType(QValueAxis::TicksFixed);
        m_axisX->setRange(0, 60);
        m_axisX->setTickInterval(5);
        m_axisY->setRange(-10, 10);
}

singleLineChart::~singleLineChart(){

}

void singleLineChart::appendSeries(double y)
{
    m_x += 0.5;
    length++;

    if(length!=0){
        m_series->append(m_x, y);
    }
    if (length > 80)
        scroll(plotArea().width()/120, 0);
}

