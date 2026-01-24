#include "relationalmodelwidget.h"
#include "ui_relationalmodelwidget.h"

#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

RelationalModelWidget::RelationalModelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RelationalModelWidget)
{
    ui->setupUi(this);

}

RelationalModelWidget::~RelationalModelWidget()
{
    delete ui;
}

void RelationalModelWidget::init()
{
    m_model = new QSqlRelationalTableModel();
    m_model->setTable("algorithms");
    m_model->setRelation(2, QSqlRelation("standart", "id", "name"));

    m_model->select();

    ui->tableView->setModel(m_model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(this));

    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);

    connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentChanged, this, &RelationalModelWidget::onCellSelected);



}

void RelationalModelWidget::onCellSelected(const QModelIndex &current, const QModelIndex &previous)
{
    if(current.isValid())
    {
        int row = current.row();
        int col = 4;//current.column();

        QModelIndex index = ui->tableView->model()->index(row, col);
        ui->textBrowser->setText(ui->tableView->model()->data(index).toString());
        index = ui->tableView->model()->index(row, 5);
        ui->textBrowser->append(ui->tableView->model()->data(index).toString());
    }
}
