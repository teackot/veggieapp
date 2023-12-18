#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <qpixmap.h>
#include <QDate>

#include "util.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qmodel = new QSqlQueryModel;
    ui->tableView->setModel(qmodel);

    ui->dateEdit->setDate(QDate::currentDate());

    connectionDialog = new ConnectionDialog;
    addDialog = new AddDialog;
    modifyDialog = new ModifyDialog;
    printDialog = new PrintDialog;

    connect(
        ui->tableView,
        SIGNAL(customContextMenuRequested(QPoint)),
        this,
        SLOT(customMenuReq(QPoint))
    );

    selectedId = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete qmodel;
    delete connectionDialog;
    delete addDialog;
    delete modifyDialog;
    delete printDialog;
}

void MainWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    on_imgInput_textChanged("img/dummy.jpg");
}

void MainWindow::on_action_triggered()
{
    connectionDialog->show();
}

void MainWindow::on_updateButton_clicked()
{
    qmodel->setQuery(
        "SELECT "
            "p.id as ID, "
            "p.name as Название, "
            "(  SELECT c.name "
            "   FROM category c "
            "   WHERE c.id = p.cat_id) "
            "   as Категория, "
            "p.img as Изображение, "
            "p.delivery_date as Поставка "
            "FROM product p"
    );
}

void MainWindow::on_addButton_clicked()
{
    addDialog->show();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int tempId;
    tempId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();

    QSqlQuery query;
    query.prepare(
        "SELECT name, cat_id, img, delivery_date "
        "FROM product "
        "WHERE id = :id"
    );
    query.bindValue(":id", tempId);

    ui->idDisplay->setText(QString::number(tempId));

    if (query.exec()) {
        query.next();

        const auto name = query.value(0).toString();
        const auto cat_id =  query.value(1).toInt();
        const auto img = query.value(2).toString();
        const auto date = query.value(3).toDate();

        const auto cats = getCategories();

        ui->nameInput->setText(name);
        ui->categoryCombo->clear();
        ui->categoryCombo->addItems(cats);
        ui->categoryCombo->setCurrentIndex(cat_id - 1);
        ui->imgInput->setText(img);
        ui->dateEdit->setDate(date);

        on_imgInput_textChanged(img);
    }
}

void MainWindow::on_imgInput_textChanged(QString text)
{
    const int labelHeight = ui->imgLabel->height();
    ui->imgLabel->setPixmap(getImagePixmap(text).scaledToHeight(labelHeight));
}

void MainWindow::on_fpickerButton_clicked()
{
    ui->imgInput->setText(QFileDialog::getOpenFileName(
        this,
        "Выбрать изображение",
        "./",
        "*.jpg"
    ));
}

void MainWindow::on_deleteButton_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM product WHERE id = :id");
    query.bindValue(":id", ui->idDisplay->text().toInt());
    query.exec();

    ui->idDisplay->clear();
    ui->nameInput->clear();
    ui->categoryCombo->clear();

    on_updateButton_clicked();
}

void MainWindow::on_editButton_clicked()
{
    QSqlQuery query;
    query.prepare(
        "UPDATE product "
        "SET name = :name, "
        "cat_id = :cat_id, "
        "img = :img, "
        "delivery_date = :date "
        "WHERE id = :id "
    );
    query.bindValue(":name", ui->nameInput->text());
    query.bindValue(":cat_id", ui->categoryCombo->currentIndex() + 1);
    query.bindValue(":img", ui->imgInput->text());
    query.bindValue(":id", ui->idDisplay->text().toInt());
    query.bindValue(":date", ui->dateEdit->date());
    query.exec();

    on_updateButton_clicked();
}

void MainWindow::customMenuReq(QPoint pos)
{
    if (qmodel->rowCount() > 0) {
        QModelIndex index = ui->tableView->indexAt(pos);
        selectedId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();

        auto *menu = new QMenu(this);
        auto *actionModify = new QAction("Изменить", this);
        auto *actionDelete = new QAction("Удалить", this);

        connect(actionModify, SIGNAL(triggered()), this, SLOT(handleActionModify()));
        connect(actionDelete, SIGNAL(triggered()), this, SLOT(handleActionDelete()));

        menu->addActions({actionModify, actionDelete});

        menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::handleActionModify()
{
    modifyDialog->setId(selectedId);
    modifyDialog->show();
}

void MainWindow::handleActionDelete()
{
    QSqlQuery query;
    query.prepare("DELETE FROM product WHERE id=:id");
    query.bindValue(":id", selectedId);
    query.exec();
    on_updateButton_clicked();
}

void MainWindow::on_exportButton_clicked()
{
    printDialog->show();
}
