#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qmodel = new QSqlQueryModel;
    ui->tableView->setModel(qmodel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    connectionDialog = new ConnectionDialog();
    connectionDialog->show();
}

void MainWindow::on_updateButton_clicked()
{
    qmodel->setQuery("SELECT * FROM product");
}
