#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class AddDialog;
}

class AddDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

private slots:
    void on_imgInput_textChanged(QString text);
    void on_fpickerButton_clicked();
    void on_addButton_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
