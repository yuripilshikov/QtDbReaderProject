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
    m_model = new QSqlTableModel();
    QSqlQueryModel* standards = new QSqlQueryModel(this);
    standards->setQuery("SELECT id FROM standart");
    ui->cbStandard->setModel(standards); // here emits the signal, calling showForDesiredStandard
    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged, this, &TableModelWidget::handleCurrentChanged);
}

void TableModelWidget::showForDesiredStandard(const QString &standard)
{
    m_model->setTable("algorithms");
    QString filter = QString("stantart = %1").arg(standard);
    qDebug() << filter;
    m_model->setFilter(filter);
    //m_model->setFilter("standart = 17");
    m_model->select();
    ui->listView->setModel(m_model);
}

void TableModelWidget::handleCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    int row = current.row();
    int col = 4;
    const auto& mdl = ui->listView->model();
    ui->textBrowser->clear();
    ui->textBrowser->append("<h1>Description</h1>");
    ui->textBrowser->append(mdl->data(mdl->index(row, 4)).toString());
    ui->textBrowser->append("<h1>Signature</h1>");
    ui->textBrowser->append(mdl->data(mdl->index(row, 5)).toString());
}
