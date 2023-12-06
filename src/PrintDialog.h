#ifndef PRINTDIALOG_H
#define PRINTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFileSelector>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QTextDocument>
#include <QTextDocumentWriter>

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

    static void writeFile(QString fname, QString text);
    static void writePdf(QString fname, QString html);
    static void writeOdt(QString fname, QString html);
};

#endif // PRINTDIALOG_H
