#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRelationalTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionConnect_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open database"), QDir::homePath(), tr("dbfiles (*.db *.sqlite);;All files(*.*)"));
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);

    if (db.open()) {
        qDebug() << "Database opened successfully:" << fileName;
//        QSqlQueryModel* model = new QSqlQueryModel(this);
//        model->setQuery("SELECT * FROM algorithms");

        auto model = new QSqlRelationalTableModel(this);
        model->setTable("algorithms");
        model->setRelation(2, QSqlRelation("standart", "id", "name"));
        model->setFilter("stantart < 11");

        //model->setFilter("department = 'Sales' AND status = 'Active'");
        //int minSalary = 50000;
        //model->setFilter(QString("salary > %1").arg(minSalary));



        model->select();
        ui->tableView->setModel(model);
    } else {
        qDebug() << "Error opening database:" << db.lastError().text();
    }



}

