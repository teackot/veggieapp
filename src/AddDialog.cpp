#include "AddDialog.h"
#include "ui_AddDialog.h"

#include <QFileDialog>
#include <QDate>

AddDialog::AddDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_imgInput_textChanged(QString text)
{
    const int labelHeight = ui->imgLabel->height();
    const QPixmap pixmap(text);
    ui->imgLabel->setPixmap(pixmap.scaledToHeight(labelHeight));
}

void AddDialog::on_fpickerButton_clicked()
{
    ui->imgInput->setText(QFileDialog::getOpenFileName(
        this,
        "Выбрать изображение",
        "./",
        "*.jpg"
    ));
}

void AddDialog::on_addButton_clicked()
{
    QSqlQuery query;
    query.prepare(
        "INSERT "
        "INTO product (name, cat_id, img, delivery_date) "
        "VALUES (:name, :cat_id, :img, :date)"
    );
    query.bindValue(":name", ui->nameInput->text());
    query.bindValue(":cat_id", ui->categoryInput->text());
    query.bindValue(":img", ui->imgInput->text());
    query.bindValue(":date", ui->dateEdit->date());

    QMessageBox msg;
    if (query.exec()) {
        close();
    } else {
        msg.setText("Ошибка");
        msg.show();
    }
}
