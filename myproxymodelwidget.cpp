#include "myproxymodelwidget.h"
#include "ui_myproxymodelwidget.h"

#include <QSqlTableModel>

#include "myproxymodel.h"


MyProxyModelWidget::MyProxyModelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyProxyModelWidget)
{
    ui->setupUi(this);


}

MyProxyModelWidget::~MyProxyModelWidget()
{
    delete ui;
}

void MyProxyModelWidget::init()
{
    QSqlTableModel* tableModel = new QSqlTableModel(this);
    tableModel->setTable("algorithms");
    tableModel->select();

    MyProxyModel* proxyModel = new MyProxyModel(this);
    proxyModel->setSourceModel(tableModel);
    proxyModel->setDisplayColumn(1);
    proxyModel->setBackgroundColumn(2);
    proxyModel->setTooltipColumn(4);
    proxyModel->setDecorationColumn(0);
    ui->listView->setModel(proxyModel);
}
