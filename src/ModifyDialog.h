#pragma once

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class ModifyDialog;
}

class ModifyDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyDialog(QWidget *parent = nullptr);
    ~ModifyDialog();

    void setId(int id);

private slots:
    void on_fnameInput_textChanged(QString text);
    void on_fpickerButton_clicked();
    void on_editButton_clicked();

private:
    Ui::ModifyDialog *ui;

    int id;

protected:
    void showEvent(QShowEvent *event) override;
};
