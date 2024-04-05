#include "voxelitem.h"
#include <QPainter>
#include <QTime>

#include "tracer/voxeltracer.h"
#include "math/transform3d.h"
#include "imagedata.h"
#include "tracer/mockdata.h"

VoxelItem::VoxelItem(QQuickItem* parent) : QQuickPaintedItem(parent),
    dataPath(nullptr)
{    
}

void VoxelItem::paint(QPainter *painter)
{
    if (tracer.getData() == nullptr)
    {
        painter->setBackground(QBrush(getBackgroundColor()));
        painter->eraseRect(boundingRect());

        return;
    }    
    painter->setTransform(QTransform().scale(1, 1));

    tracer.setTransform(
        math::lh::newRotationX(angleX) *
        math::lh::newRotationY(angleY) *
        math::lh::newRotationZ(angleZ)
    );

    VoxelCanvas canvas(painter);

    QTime time;
    time.start();
    tracer.render(canvas);
    qDebug() << "Render time: " << time.elapsed();
}

void VoxelItem::setDataPath(QUrl path) {
    QDir dir(path.toLocalFile());
    if (!dir.exists())
    {
        tracer.setData(nullptr);
        update();
        return;
    }

    this->dataPath = path;    
    std::shared_ptr<Data> data(new ImageData(dir));
    tracer.setData(data->getDepth() == 0 ? nullptr : data);
    update();
}

QUrl VoxelItem::getDataPath() const
{
    return dataPath;
}

void VoxelItem::setAngleX(qreal angle)
{
    angleX = math::toRadians(angle);
    update();
}

qreal VoxelItem::getAngleX() const
{
    return angleX;
}

void VoxelItem::setAngleY(qreal angle)
{
    angleY = math::toRadians(angle);
    update();
}

qreal VoxelItem::getAngleY() const
{
    return angleY;
}

void VoxelItem::setAngleZ(qreal angle)
{
    angleZ = math::toRadians(angle);
    update();
}

qreal VoxelItem::getAngleZ() const
{
    return angleZ;
}

void VoxelItem::setCameraDistance(qreal distance)
{
    float dist = static_cast<float>(distance);
    if (math::equals(tracer.getCameraDistance(), dist)) {
        return;
    }

    tracer.setCameraDistance(dist);
    update();
}

qreal VoxelItem::getCameraDistance() const
{
    return tracer.getCameraDistance();
}

void VoxelItem::setDraft(bool d)
{
    if (d == tracer.isDraft())
        return;

    tracer.setDraft(d);
    update();
}

bool VoxelItem::isDraft() const
{
    return tracer.isDraft();
}



void VoxelItem::setBackgroundColor(const QColor& color)
{
    math::Vector3 bgColor(color.redF(), color.greenF(), color.blueF());
    if (bgColor == tracer.getBackgroundColor())
        return;

    tracer.setBackgroundColor(bgColor);
    update();
}

const QColor VoxelItem::getBackgroundColor() const
{
    math::Vector3 bg = tracer.getBackgroundColor();
    return QColor::fromRgbF(bg.r(), bg.g(), bg.b());
}

void VoxelItem::setTransparencyColor(const QColor& color)
{
    math::Vector3 transparencyColor(color.redF(), color.greenF(), color.blueF());
    if (transparencyColor == tracer.getTransparencyColor())
        return;

    tracer.setTransparencyColor(transparencyColor);
    update();
}

const QColor VoxelItem::getTransparencyColor() const
{
    math::Vector3 c = tracer.getTransparencyColor();
    return QColor::fromRgbF(c.r(), c.g(), c.b());
}

void VoxelItem::setTransparencyTolerance(qreal tolerance)
{
    tracer.setTransparencyTolerance(tolerance);
}

qreal VoxelItem::getTransparencyTolerance() const
{
    return tracer.getTransparencyTolerance();
}

void VoxelItem::setVoxelSize(const QVector3D& voxelSize)
{
    math::Vector3 size(voxelSize.x(), voxelSize.y(), voxelSize.z());
    if (tracer.getVoxelSize() == size)
        return;

    tracer.setVoxelSize(size);
    update();
}

const QVector3D VoxelItem::getVoxelSize() const
{
    return QVector3D(tracer.getVoxelSize().x(), tracer.getVoxelSize().y(), tracer.getVoxelSize().z());
}

void VoxelItem::setNumThreads(int number)
{
    tracer.setNumThreads(number);
}

int VoxelItem::getNumThreads() const
{
    return tracer.getNumThreads();
}
