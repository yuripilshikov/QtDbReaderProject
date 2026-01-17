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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->actionConnect_to_database, &QAction::triggered, this, &MainWindow::connectDB);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCellSelected(const QModelIndex &current, const QModelIndex &previous)
{
    if(current.isValid())
    {
        int row = current.row();
        int col = 4;//current.column();

        QModelIndex index = ui->tableView->model()->index(row, col);
        ui->textBrowser->setText(ui->tableView->model()->data(index).toString());
    }
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
        // fill the form
        QSqlRelationalTableModel* model = new QSqlRelationalTableModel();
        model->setTable("algorithms");
        model->setRelation(2, QSqlRelation("standart", "id", "name"));

        model->select();
        ui->tableView->setModel(model);
        ui->tableView->setItemDelegate(new QSqlRelationalDelegate(this));
        // do not show description in table
        ui->tableView->hideColumn(4);

        // set status bar
        ui->statusbar->showMessage("Opened database: " + db.databaseName());

        // connect
        connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::onCellSelected);
    }
    else
    {
        qDebug() << "Error opening database:" << db.lastError().text();
    }

}

