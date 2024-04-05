#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include "tracer/data.h"
#include <vector>
#include <QDir>
#include <QImage>

class ImageData : public Data
{
    private:
        std::vector<QImage> data;

    public:
        ImageData(const QDir& images);
        virtual int getWidth() const override;
        virtual int getHeight() const override;
        virtual int getDepth() const override;
        virtual math::Vector3 get(int x, int y, int z) override;
};

#endif // IMAGEDATA_H
