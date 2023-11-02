#pragma once

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

#ifdef _WIN32
#define SQL_DRIVER_NAME "SQL Server"
#endif

#ifdef __linux__
#define SQL_DRIVER_NAME "/opt/microsoft/msodbcsql18/lib64/libmsodbcsql-18.3.so.2.1"
#endif

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();
    QMessageBox *responseMsg;

private slots:
    void on_connectButton_clicked();
    void on_responseMsg_finished(int result);

private:
    Ui::ConnectionDialog *ui;
    QSqlDatabase db;
};
