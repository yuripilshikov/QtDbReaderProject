#include "relationalmodelwidget.h"
#include "ui_relationalmodelwidget.h"

#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

#include "mysqlrelationaldelegate.h"

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
    ui->tableView->setItemDelegate(new MySqlRelationalDelegate(this));

    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);
    ui->tableView->resizeColumnsToContents();
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentChanged, this, &RelationalModelWidget::onCellSelected);
}

void RelationalModelWidget::onCellSelected(const QModelIndex &current, const QModelIndex &previous)
{
    if(current.isValid())
    {
        int row = current.row();
        const auto& mdl = ui->tableView->model();
        QString str(QString("#  %4\n ## Description \n %1 \n\n ## Signature \n ``` %2 \n``` \n\n ## Snippet\n ``` %3 \n```")
                            .arg(mdl->data(mdl->index(row, 4)).toString())
                            .arg(mdl->data(mdl->index(row, 6)).toString())
                            .arg(mdl->data(mdl->index(row, 5)).toString())
                            .arg(mdl->data(mdl->index(row, 1)).toString()));
        ui->textBrowser->setMarkdown(str);
    }
}
