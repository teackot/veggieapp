#include "ConnectionDialog.h"
#include "ui_ConnectionDialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_connectButton_clicked()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(
        "DRIVER={" SQL_DRIVER_NAME "}"
        ";SERVER=" + ui->serverNameInput->text() +
        ";DATABASE=" + ui->dbNameInput->text() +
        ";TrustServerCertificate=yes" ";"
    );
    db.setUserName(ui->usernameInput->text());
    db.setPassword(ui->passwordInput->text());

    responseMsg = new QMessageBox;

    if (db.open()) {
        responseMsg->setText("Success");
        connect(responseMsg, SIGNAL(finished(int)), this, SLOT(on_responseMsg_finished(int)));
    } else {
        responseMsg->setText("DB connection error:\n'" + db.lastError().text() + "'");
    }

    responseMsg->show();
}

void ConnectionDialog::on_responseMsg_finished(int result)
{
    close();
}
