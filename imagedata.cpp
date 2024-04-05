#include "imagedata.h"
#include <QColor>

ImageData::ImageData(const QDir &images)
{
    QFileInfoList files = images.entryInfoList(QDir::Files, QDir::Name);
    foreach (QFileInfo file, files)
    {
        if (file.isFile())
        {
            QImage img(file.absoluteFilePath());
            if (!img.isNull())
                data.push_back(img);
        }
    }
}

int ImageData::getWidth() const
{
    return data.size() == 0 ? 0 : data[0].width();
}

int ImageData::getHeight() const
{
    return data.size() == 0 ? 0 : data[0].height();
}

int ImageData::getDepth() const
{
    return data.size();
}

math::Vector3 ImageData::get(int x, int y, int z)
{
    if (z < 0 || z >= data.size() ||
        x < 0 || x >= data[z].width() ||
        y < 0 || y >= data[z].height())
    {
        return math::Vector3();
    }

    QColor color = QColor(data[z].pixel(x, y));
    return math::Vector3(color.redF(), color.greenF(), color.blueF());
}

