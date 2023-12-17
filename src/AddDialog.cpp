#include "AddDialog.h"
#include "ui_AddDialog.h"

#include "src/util.h"

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

void AddDialog::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    
    ui->categoryCombo->clear();
    ui->categoryCombo->addItems(getCategories());
    ui->categoryCombo->setCurrentIndex(0);
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
    query.bindValue(":cat_id", ui->categoryCombo->currentIndex() + 1);
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
