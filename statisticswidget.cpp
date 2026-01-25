#include "statisticswidget.h"
#include "ui_statisticswidget.h"

#include <QSqlQuery>
#include <QVector>

StatisticsWidget::StatisticsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsWidget)
{
    ui->setupUi(this);



}



StatisticsWidget::~StatisticsWidget()
{
    delete ui;
}

void StatisticsWidget::init()
{
    // get data for all standards
    QSqlQuery query;
    QPieSeries* series = new QPieSeries();
    query.exec("select count(id) from algorithms where stantart=3");
    if(query.next())
    {
        series->append("C++03", query.value(0).toInt());
    }

    query.exec("select count(id) from algorithms where stantart=11");
    if(query.next())
    {
        series->append("C++11", query.value(0).toInt());
    }

    query.exec("select count(id) from algorithms where stantart=14");
    if(query.next())
    {
        series->append("C++14", query.value(0).toInt());
    }

    query.exec("select count(id) from algorithms where stantart=17");
    if(query.next())
    {
        series->append("C++17", query.value(0).toInt());
    }

    query.exec("select count(id) from algorithms where stantart=20");
    if(query.next())
    {
        series->append("C++20", query.value(0).toInt());
    }

    query.exec("select count(id) from algorithms where stantart=23");
    if(query.next())
    {
        series->append("C++23", query.value(0).toInt());
    }

    // colors
    QVector<QColor> colors{{0x78, 0, 0, 123}, {0xC1, 0x12, 0x1F, 123}, {0xFD, 0xF0, 0xD5, 123},
                  {0, 0x30, 0x49, 123}, {0x66, 0x9B, 0xBC, 123}, {0, 0x96, 0xC7, 123}};

    int count = series->slices().count();
    for(int i = 0; i < count; ++i)
    {
        QPieSlice* slice = series->slices().at(i);
        slice->setExploded(true);
        slice->setLabelVisible(true);
        slice->setPen(colors.at(i).darker());
        slice->setBrush(colors.at(i));
    }



    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("Algorithms by standards (unique)"));

    QChartView* chartView = new QChartView(chart);
    ui->verticalLayout->addWidget(chartView);
}
