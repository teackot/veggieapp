#include "ConnectionDialog.h"
#include "ui_ConnectionDialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    ui->serverNameInput->setText(SQL_DEFAULT_SERVER);
    ui->dbNameInput->setText(SQL_DEFAULT_DB_NAME);
    ui->usernameInput->setText(SQL_DEFAULT_UNAME);
    ui->passwordInput->setText(SQL_DEFAULT_PASSWD);

    auto db = QSqlDatabase::addDatabase("QODBC3");
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
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

    auto responseMsg = new QMessageBox(this);

    if (db.open()) {
        responseMsg->setText("Успешно");
        QMetaObject::Connection connection = connect(
            responseMsg,
            &QMessageBox::finished,
            this,
            [this, responseMsg](int result) {
                close();
                responseMsg->disconnect(this);
            }
        );
    } else {
        responseMsg->setText("Ошибка при подключении к БД:\n'" + db.lastError().text() + "'");
    }

    responseMsg->show();
}
