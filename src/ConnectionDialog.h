#pragma once

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

#define SQL_DEFAULT_DB_NAME "veggieapp"

#ifdef _WIN32
#define SQL_DRIVER_NAME "SQL Server"
#define SQL_DEFAULT_SERVER ".\\SQLEXPRESS"
#define SQL_DEFAULT_UNAME ""
#define SQL_DEFAULT_PASSWD ""
#endif

#ifdef __linux__
#define SQL_DRIVER_NAME "/opt/microsoft/msodbcsql18/lib64/libmsodbcsql-18.3.so.2.1"
#define SQL_DEFAULT_SERVER "localhost"
#define SQL_DEFAULT_UNAME "SA"
#define SQL_DEFAULT_PASSWD "<YourStrong@Passw0rd>"
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

private slots:
    void on_connectButton_clicked();
    void on_revealButton_toggled(bool checked);

private:
    Ui::ConnectionDialog *ui;
};
