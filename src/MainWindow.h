#pragma once

#include <QMainWindow>
#include <QSqlQueryModel>
#include "ConnectionDialog.h"
#include "AddDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_updateButton_clicked();
    void on_addButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_editButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;

    QSqlQueryModel *qmodel;

    ConnectionDialog *connectionDialog;
    AddDialog *addDialog;
};
