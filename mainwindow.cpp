#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRelationalTableModel>
#include <QAbstractItemView>
#include <QSqlRelationalDelegate>
#include <QTableView>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionConnect_to_database, &QAction::triggered, this, &MainWindow::connectDB);

    // init query widget
    connect(this, &MainWindow::dbConnected, ui->queryWidget, &QueryModelWidget::showData);

    // init table widget
    connect(this, &MainWindow::dbConnected, ui->tableWidget, &TableModelWidget::init);

    // init relational table widget
    connect(this, &MainWindow::dbConnected, ui->relationalWidget, &RelationalModelWidget::init);

    // init statistics
    connect(this, &MainWindow::dbConnected, ui->widget, &StatisticsWidget::init);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connectDB()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open database")
                , QDir::homePath(),
                tr("dbfiles (*.db *.sqlite);;All files(*.*)"));
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);

    if(db.open())
    {
        emit dbConnected();
        ui->statusbar->showMessage("Opened database: " + db.databaseName());
    }
    else
    {
        qDebug() << "Error opening database:" << db.lastError().text();
    }

}

