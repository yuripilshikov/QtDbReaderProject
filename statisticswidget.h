#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>

#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>

namespace Ui {
class StatisticsWidget;
}

class StatisticsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWidget(QWidget *parent = nullptr);
    ~StatisticsWidget();

private:
    Ui::StatisticsWidget *ui;

public slots:
    void init();
};

#endif // STATISTICSWIDGET_H
