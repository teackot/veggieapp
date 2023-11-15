#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qmodel = new QSqlQueryModel;
    ui->tableView->setModel(qmodel);

    connectionDialog = new ConnectionDialog;
    addDialog = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete qmodel;
    delete connectionDialog;
    delete addDialog;
}

void MainWindow::on_action_triggered()
{
    connectionDialog->show();
}

void MainWindow::on_updateButton_clicked()
{
    qmodel->setQuery("SELECT * FROM product");
}

void MainWindow::on_addButton_clicked()
{
    addDialog = new AddDialog;
    addDialog->show();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int tempId;
    tempId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();

    QSqlQuery query;
    query.prepare("SELECT name, cat_id FROM product WHERE id = :id");
    query.bindValue(":id", tempId);

    ui->idDisplay->setText(QString::number(tempId));

    if (query.exec()) {
        query.next();
        ui->nameInput->setText(query.value(0).toString());
        ui->categoryInput->setText(query.value(1).toString());
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM product WHERE id = :id");
    query.bindValue(":id", ui->idDisplay->text().toInt());
    query.exec();

    ui->idDisplay->clear();
    ui->nameInput->clear();
    ui->categoryInput->clear();

    on_updateButton_clicked();
}

void MainWindow::on_editButton_clicked()
{
    QSqlQuery query;
    query.prepare("UPDATE product SET name = :name, cat_id = :cat_id  WHERE id = :id");
    query.bindValue(":name", ui->nameInput->text());
    query.bindValue(":cat_id", ui->categoryInput->text());
    query.bindValue(":id", ui->idDisplay->text().toInt());
    query.exec();

    on_updateButton_clicked();
}
