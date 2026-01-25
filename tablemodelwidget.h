#ifndef TABLEMODELWIDGET_H
#define TABLEMODELWIDGET_H

#include <QWidget>
#include "mysqltablemodel.h"

class QSqlTableModel;

namespace Ui {
class TableModelWidget;
}

class TableModelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableModelWidget(QWidget *parent = nullptr);
    ~TableModelWidget();

private:
    Ui::TableModelWidget *ui;

    //QSqlTableModel* m_model;
    MySqlTableModel* m_model;

public slots:
    void init();
    void showForDesiredStandard(const QString& standard);
    void handleCurrentChanged(const QModelIndex& current, const QModelIndex& previous);
};

#endif // TABLEMODELWIDGET_H
