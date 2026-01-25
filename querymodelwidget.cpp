#include "querymodelwidget.h"
#include "ui_querymodelwidget.h"

#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>


QueryModelWidget::QueryModelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryModelWidget)
{
    ui->setupUi(this);
    m_model = new MySqlQueryModel();
    connect(ui->cbStandard, &QComboBox::currentTextChanged, this, &QueryModelWidget::showForDesiredStandard);
}

QueryModelWidget::~QueryModelWidget()
{
    delete ui;
}

void QueryModelWidget::showData()
{
    QSqlQueryModel* standards = new QSqlQueryModel(this);
    standards->setQuery("SELECT id FROM standart");
    ui->cbStandard->setModel(standards);
    ui->listView->setModel(m_model);
    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged, this, &QueryModelWidget::handleCurrentChanged);
}

void QueryModelWidget::showForDesiredStandard(const QString& standard)
{
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
    query.prepare("SELECT description, signature, snippet FROM algorithms WHERE stantart = :st AND name = :nm");
    query.bindValue(":st", ui->cbStandard->currentText());
    query.bindValue(":nm", ui->listView->model()->data(current).toString());
    query.exec();
    QString str2 = "";
    while(query.next())
    {        
        QString description = query.value(query.record().indexOf("description")).toString();
        QString signature = query.value(query.record().indexOf("signature")).toString();
        QString snippet = query.value(query.record().indexOf("snippet")).toString();
        QString str(QString("#  %4\n ## Description \n %1 \n\n ## Signature \n ``` %2 \n``` \n\n ## Snippet\n ``` %3 \n```")
                    .arg(description)
                    .arg(signature)
                    .arg(snippet)
                    .arg(ui->listView->model()->data(current).toString()));
        ui->textBrowser->setMarkdown(str);
    }
}
