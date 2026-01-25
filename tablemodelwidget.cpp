#include "tablemodelwidget.h"
#include "ui_tablemodelwidget.h"

#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QAbstractItemModel>

#include <QSqlQuery>

TableModelWidget::TableModelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableModelWidget)
{
    ui->setupUi(this);

    connect(ui->cbStandard, &QComboBox::currentTextChanged, this, &TableModelWidget::showForDesiredStandard);
}

TableModelWidget::~TableModelWidget()
{
    delete ui;
}

void TableModelWidget::init()
{
    m_model = new MySqlTableModel();
    QSqlQueryModel* standards = new QSqlQueryModel(this);
    standards->setQuery("SELECT id FROM standart");
    ui->cbStandard->setModel(standards); // here emits the signal, calling showForDesiredStandard
    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged, this, &TableModelWidget::handleCurrentChanged);
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentChanged, this, &TableModelWidget::handleCurrentChanged);
}

void TableModelWidget::showForDesiredStandard(const QString &standard)
{
    m_model->setTable("algorithms");
    QString filter = QString("stantart = %1").arg(standard);
    qDebug() << filter;
    m_model->setFilter(filter);
    m_model->select();
    ui->listView->setModel(m_model);
    ui->tableView->setModel(m_model);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);
}

void TableModelWidget::handleCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    int row = current.row();
    int col = 4;
    const auto& mdl = ui->listView->model();
    ui->textBrowser->clear();

    QString str(QString("#  %4\n ## Description \n %1 \n\n ## Signature \n ``` %2 \n``` \n\n ## Snippet\n ``` %3 \n```")
                        .arg(mdl->data(mdl->index(row, 4)).toString())
                        .arg(mdl->data(mdl->index(row, 6)).toString())
                        .arg(mdl->data(mdl->index(row, 5)).toString())
                        .arg(ui->listView->model()->data(current).toString()));
    ui->textBrowser->setMarkdown(str);
}
