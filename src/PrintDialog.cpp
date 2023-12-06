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
    QString filter;
    if (ui->htmlRadio->isChecked()) {
        filter = "*.html";
    } else if (ui->pdfRadio->isChecked()) {
        filter = "*.pdf";
    } else if (ui->odtRadio->isChecked()) {
        filter = "*.odt";
    }

    ui->fnameInput->setText(QFileDialog::getSaveFileName(
        this,
        "Экспортировать как",
        "./",
        filter
    ));
}

void PrintDialog::on_exportButton_clicked()
{
    // build HTML
    QString html;
    QTextStream stream(&html);
    stream << "<html>";
        stream << "<head/>";
        stream << "<body>";
            stream << "<center>";
                stream << QString("Отчет");
                stream << "<table border=1>";
                    stream << "<tr>";
                        stream << "<td>" << "ID" << "</td>";
                        stream << "<td>" << QString("Наименование") << "</td>";
                        stream << "<td>" << QString("Категория") << "</td>";
                    stream << "</tr>";

                    QSqlQuery query;
                    query.exec("SELECT * FROM product");
                    while (query.next()) {
                        stream << "<tr>";
                            stream << "<td>" << query.value(0).toString() << "</td>";
                            stream << "<td>" << query.value(1).toString() << "</td>";
                            stream << "<td>" << query.value(2).toString() << "</td>";
                        stream << "</tr>";
                    }

                stream << "</table>";
            stream << "</center>";
        stream << "</body>";
    stream << "</html>";

    auto fname = ui->fnameInput->text();
    if (ui->htmlRadio->isChecked()) {
        writeFile(fname, html);
    } else if (ui->pdfRadio->isChecked()) {
        writePdf(fname, html);
    } else if (ui->odtRadio->isChecked()) {
        writeOdt(fname, html);
    }
}

void PrintDialog::writeFile(QString fname, QString text)
{
    QFile file;
    file.setFileName(fname);
    file.open(QIODevice::WriteOnly);

    file.write(text.toUtf8());

    file.close();
}

void PrintDialog::writePdf(QString fname, QString html)
{
    QPrinter printer;
    printer.setPageOrientation(QPageLayout::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFileName(fname);

    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&printer);
}

void PrintDialog::writeOdt(QString fname, QString html)
{
    QTextDocument doc;
    doc.setHtml(html);

    QTextDocumentWriter writer(fname, "odf");
    writer.write(&doc);
}
