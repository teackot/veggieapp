#pragma once

#include <QString>
#include <QStringList>
#include <QPixmap>
#include <qpixmap.h>

[[nodiscard]] QString getCategoryName(int cat_id);
[[nodiscard]] QStringList getCategories();

[[nodiscard]] QPixmap getImagePixmap(QString path);
