#include "ModifyDialog.h"
#include "ui_ModifyDialog.h"

#include "src/util.h"

#include <QFileDialog>

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

void ModifyDialog::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    on_fnameInput_textChanged(ui->fnameInput->text());
}

void ModifyDialog::setId(int id)
{
    this->id = id;

    QSqlQuery query;
    query.prepare("SELECT "
        "name, cat_id, img, delivery_date "
        "FROM product "
        "WHERE id=?"
    );
    query.bindValue(0, id);
    if (query.exec()) {
        query.next();
        ui->nameInput->setText(query.value(0).toString());
        ui->categoryCombo->clear();
        ui->categoryCombo->addItems(getCategories());
        ui->categoryCombo->setCurrentIndex(query.value(1).toInt() - 1);
        ui->fnameInput->setText(query.value(2).toString());
        ui->dateEdit->setDate(query.value(3).toDate());
    }
}

void ModifyDialog::on_fnameInput_textChanged(QString text)
{
    const int labelHeight = ui->imgLabel->height();
    const QPixmap pixmap(text);
    ui->imgLabel->setPixmap(pixmap.scaledToHeight(labelHeight));
}

void ModifyDialog::on_fpickerButton_clicked()
{
    ui->fnameInput->setText(QFileDialog::getOpenFileName(
        this,
        "Выбрать изображение",
        "./",
        "*.jpg"
    ));
}

void ModifyDialog::on_editButton_clicked()
{
    QSqlQuery query;
    query.prepare(
        "UPDATE product "
        "SET "
            "name = :name, "
            "cat_id = :cat_id, "
            "img = :img, "
            "delivery_date = :date "
        "WHERE id = :id "
    );
    query.bindValue(":name", ui->nameInput->text());
    query.bindValue(":cat_id", ui->categoryCombo->currentIndex() + 1);
    query.bindValue(":img", ui->fnameInput->text());
    query.bindValue(":date", ui->dateEdit->date());
    query.bindValue(":id", id);

    if (query.exec()) {
        close();
    }
}

