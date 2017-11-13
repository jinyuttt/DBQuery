#ifndef DBMONITER_H
#define DBMONITER_H

#include <QWidget>
#include "QtCharts/QChart"
#include "QLineSeries"
#include "QValueAxis"
#include "QTimer"
#include "QTime"
#include "QList"
#include "qmath.h"
#include "QPointF"
#include "QDebug"
#include <QtCharts>
#include<QVBoxLayout>
namespace Ui {
class DBMoniter;
}

class DBMoniter : public QWidget
{
    Q_OBJECT

public:
    explicit DBMoniter(QWidget *parent = 0);
    ~DBMoniter();

private:
    Ui::DBMoniter *ui;
    QChart *m_chart;
    QLineSeries *m_series;
    //QList<double> dataList;//存储业务数据
    int maxSize = 5000;
    int timeId=0;
protected:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
private:
    double getData(double time);
};

#endif // DBMONITER_H
