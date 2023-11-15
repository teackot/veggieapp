#include "ConnectionDialog.h"
#include "ui_ConnectionDialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    ui->serverNameInput->setText("localhost");
    ui->dbNameInput->setText("veggieapp");
    ui->usernameInput->setText("SA");
    ui->passwordInput->setText("<YourStrong@Passw0rd>");

    responseMsg = new QMessageBox;

    auto db = QSqlDatabase::addDatabase("QODBC3");
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
    delete responseMsg;
}

void ConnectionDialog::on_connectButton_clicked()
{
    auto db = QSqlDatabase::database("qt_sql_default_connection", false);

    if (db.isOpen()) {
        db.close();
    }

    db.setDatabaseName(
        "DRIVER={" SQL_DRIVER_NAME "}"
        ";SERVER=" + ui->serverNameInput->text() +
        ";DATABASE=" + ui->dbNameInput->text() +
        ";TrustServerCertificate=yes" ";"
    );
    db.setUserName(ui->usernameInput->text());
    db.setPassword(ui->passwordInput->text());

    if (db.open()) {
        responseMsg->setText("Успешно");
        connect(responseMsg, SIGNAL(finished(int)), this, SLOT(responseMsg_finished(int)));
    } else {
        responseMsg->setText("Ошибка при подключении к БД:\n'" + db.lastError().text() + "'");
    }

    responseMsg->show();
}

void ConnectionDialog::responseMsg_finished(int result)
{
    close();
}
