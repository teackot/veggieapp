#include "PrintDialog.h"
#include "ui_PrintDialog.h"

PrintDialog::PrintDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintDialog)
{
    ui->setupUi(this);
}

PrintDialog::~PrintDialog()
{
    delete ui;
}

void PrintDialog::on_fpickerButton_clicked()
{
    ui->fnameInput->setText(QFileDialog::getOpenFileName(0, "Выберите файл", "./", "*.html"));
}

void PrintDialog::on_exportButton_clicked()
{
    QFile file;
    file.setFileName(ui->fnameInput->text());
    file.open(QIODevice::WriteOnly);

    QTextStream in(&file);
    in << "<html>";
        in << "<head/>";
        in << "<body>";
            in << "<center>";
                in << "Пример создания отчета";
                in << "<table border=1>";
                    in << "<tr>";
                        in << "<td>" << "ID" << "</td>";
                        in << "<td>" << "Наименование" << "</td>";
                        in << "<td>" << "Категория" << "</td>";
                    in << "</tr>";

                    QSqlQuery query;
                    query.exec("SELECT * FROM product");
                    while (query.next()) {
                        in << "<tr>";
                            in << "<td>" << query.value(0).toString() << "</td>";
                            in << "<td>" << query.value(1).toString() << "</td>";
                            in << "<td>" << query.value(2).toString() << "</td>";
                        in << "</tr>";
                    }

                in << "</table>";
            in << "</center>";
        in << "</body>";
    in << "</html>";

    // QPrinter printer;
    // printer.setOrientation(QPrinter::Portrait);
    // printer.setOutputFormat(QPrinter::PdfFormat);
    // printer.setPaperSize(QPrinter::A4);
    // printer.setOutputFileName(file.fileName() + ".pdf");

    // QTextDocument doc;
    // doc.setHtml(in.readAll());
    // doc.print(&printer);
    
    file.close();
}

