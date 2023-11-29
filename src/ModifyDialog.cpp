#include "ModifyDialog.h"
#include "ui_ModifyDialog.h"

ModifyDialog::ModifyDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyDialog)
{
    ui->setupUi(this);
}

ModifyDialog::~ModifyDialog()
{
    delete ui;
}

void ModifyDialog::setId(int id)
{
    this->id = id;

    QSqlQuery query;
    query.prepare("SELECT name, cat_id FROM product WHERE id=?");
    query.bindValue(0, id);
    if (query.exec()) {
        query.next();
        ui->nameInput->setText(query.value(0).toString());
        ui->categoryInput->setText(query.value(1).toString());
    }
}

void ModifyDialog::on_editButton_clicked()
{
    QSqlQuery query;
    query.prepare("UPDATE product SET name = :name, cat_id = :cat_id  WHERE id = :id");
    query.bindValue(":name", ui->nameInput->text());
    query.bindValue(":cat_id", ui->categoryInput->text());
    query.bindValue(":id", id);

    if (query.exec()) {
        close();
    }
}

