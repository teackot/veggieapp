#ifndef PRINTDIALOG_H
#define PRINTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QTextDocument>

namespace Ui {
class PrintDialog;
}

class PrintDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PrintDialog(QWidget *parent = nullptr);
    ~PrintDialog();

private slots:
    void on_fpickerButton_clicked();
    void on_exportButton_clicked();

private:
    Ui::PrintDialog *ui;
};

#endif // PRINTDIALOG_H
