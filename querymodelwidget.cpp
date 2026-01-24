#include "querymodelwidget.h"
#include "ui_querymodelwidget.h"

#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>


QueryModelWidget::QueryModelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryModelWidget),
    m_model(new QSqlQueryModel)
{
    ui->setupUi(this);
    connect(ui->cbStandard, &QComboBox::currentTextChanged, this, &QueryModelWidget::showForDesiredStandard);
}

QueryModelWidget::~QueryModelWidget()
{
    delete ui;
}

void QueryModelWidget::showData()
{
    //qDebug() << "QueryModelwidget!";

    QSqlQueryModel* standards = new QSqlQueryModel(this);
    standards->setQuery("SELECT id FROM standart");
    ui->cbStandard->setModel(standards);
    //showForDesiredStandard(ui->cbStandard->currentText());
    ui->listView->setModel(m_model);
    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged, this, &QueryModelWidget::handleCurrentChanged);


}

void QueryModelWidget::showForDesiredStandard(const QString& standard)
{
    //qDebug() << "show for desired standard " << standard;
    QSqlQuery query;
    query.prepare("SELECT name FROM algorithms WHERE stantart = :st");
    query.bindValue(":st", ui->cbStandard->currentText());
    query.exec();
    m_model->setQuery(query);
}

void QueryModelWidget::handleCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    qDebug() << ui->listView->model()->data(current);
    ui->textBrowser->clear();
    QSqlQuery query;
    query.prepare("SELECT description, signature FROM algorithms WHERE stantart = :st AND name = :nm");
    query.bindValue(":st", ui->cbStandard->currentText());
    query.bindValue(":nm", ui->listView->model()->data(current).toString());
    query.exec();
    while(query.next())
    {        
        ui->textBrowser->append("<h1>Description</h1>");
        ui->textBrowser->append(query.value(query.record().indexOf("description")).toString());
        ui->textBrowser->append("<h1>Signature</h1>");
        ui->textBrowser->append(query.value(query.record().indexOf("signature")).toString());
    }
}
