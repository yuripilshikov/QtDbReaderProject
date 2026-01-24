#ifndef RELATIONALMODELWIDGET_H
#define RELATIONALMODELWIDGET_H

#include <QWidget>

class QSqlRelationalTableModel;

namespace Ui {
class RelationalModelWidget;
}

class RelationalModelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RelationalModelWidget(QWidget *parent = nullptr);
    ~RelationalModelWidget();

private:
    Ui::RelationalModelWidget *ui;
    QSqlRelationalTableModel* m_model;

public slots:
    void init();
    void onCellSelected(QModelIndex const& current, QModelIndex const& previous);
};

#endif // RELATIONALMODELWIDGET_H
