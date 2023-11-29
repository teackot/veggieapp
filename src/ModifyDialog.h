#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

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
    void on_editButton_clicked();

private:
    Ui::ModifyDialog *ui;

    int id;
};

#endif // MODIFYDIALOG_H
