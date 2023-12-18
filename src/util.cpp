#include "util.h"

#include <QVariant>
#include <QSqlError>
#include <QSqlResult>
#include <QSqlQuery>
#include <qpixmap.h>

QString getCategoryName(int cat_id)
{
    QSqlQuery query;
    query.prepare(
        "SELECT name "
        "FROM category "
        "WHERE id = :id"
    );
    query.bindValue(":id", cat_id);

    if (query.exec()) {
        query.next();
        return query.value(0).toString();
    }

    return "";
}

QStringList getCategories()
{
    QSqlQuery query;
    query.prepare(
        "SELECT name "
        "FROM category"
    );

    QStringList cats;
    if (query.exec()) {
        while (query.next())
            cats += query.value(0).toString();
    }

    return cats;
}

QPixmap getImagePixmap(QString path)
{
    const QPixmap pixmap = QPixmap(path);

    if (pixmap.isNull())
        return QPixmap("img/dummy.jpg");

    return pixmap;
}
