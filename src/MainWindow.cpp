#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qmodel = nullptr;

    connectionDialog = new ConnectionDialog;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete qmodel;
    delete connectionDialog;
}

void MainWindow::on_action_triggered()
{
    delete qmodel;
    connectionDialog->show();
    qmodel = new QSqlQueryModel;
    ui->tableView->setModel(qmodel);
}

void MainWindow::on_updateButton_clicked()
{
    qmodel->setQuery("SELECT * FROM product");
}
