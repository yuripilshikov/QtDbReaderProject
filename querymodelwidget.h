#ifndef QUERYMODELWIDGET_H
#define QUERYMODELWIDGET_H

#include <QWidget>
#include "mysqlquerymodel.h"

class QSqlQueryModel;

namespace Ui {
class QueryModelWidget;
}

class QueryModelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QueryModelWidget(QWidget *parent = nullptr);
    ~QueryModelWidget();

private:
    Ui::QueryModelWidget *ui;
    //QSqlQueryModel* m_model;
    MySqlQueryModel* m_model;

public slots:
    void showData();
    void showForDesiredStandard(const QString& standard);
    void handleCurrentChanged(const QModelIndex& current, const QModelIndex& previous);
};

#endif // QUERYMODELWIDGET_H
