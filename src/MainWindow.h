#pragma once

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QPoint>
#include <QMenu>
#include <QAction>

#include "ConnectionDialog.h"
#include "AddDialog.h"
#include "ModifyDialog.h"
#include "PrintDialog.h"

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

    void handleActionModify();
    void handleActionDelete();

    void customMenuReq(QPoint pos);

    void on_exportButton_clicked();

private:
    Ui::MainWindow *ui;

    QSqlQueryModel *qmodel;

    ConnectionDialog *connectionDialog;
    AddDialog *addDialog;
    ModifyDialog *modifyDialog;
    PrintDialog *printDialog;

    int selectedId;
};
