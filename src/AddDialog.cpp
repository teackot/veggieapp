#include "AddDialog.h"
#include "ui_AddDialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_addButton_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO product (name, cat_id) VALUES (:name, :cat_id)");
    query.bindValue(":name", ui->nameInput->text());
    query.bindValue(":cat_id", ui->categoryInput->text());

    QMessageBox msg;
    if (query.exec()) {
        close();
    } else {
        msg.setText("Ошибка");
        msg.show();
    }
}
