#ifndef VOXELITEM_H
#define VOXELITEM_H

#include <QQuickPaintedItem>
#include <QUrl>
#include <QPainter>
#include <QImage>
#include <QColor>
#include <QVector3D>

#include "tracer/canvas.h"
#include "tracer/voxeltracer.h"

class VoxelItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QUrl dataPath READ getDataPath WRITE setDataPath NOTIFY dataChanged)
    Q_PROPERTY(qreal angleX READ getAngleX WRITE setAngleX)
    Q_PROPERTY(qreal angleY READ getAngleY WRITE setAngleY)
    Q_PROPERTY(qreal angleZ READ getAngleZ WRITE setAngleZ)
    Q_PROPERTY(qreal cameraDistance READ getCameraDistance WRITE setCameraDistance)
    Q_PROPERTY(bool draft READ isDraft WRITE setDraft)
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor transparencyColor READ getTransparencyColor WRITE setTransparencyColor)
    Q_PROPERTY(qreal transparencyTolerance READ getTransparencyTolerance WRITE setTransparencyTolerance)
    Q_PROPERTY(QVector3D voxelSize READ getVoxelSize WRITE setVoxelSize)
    Q_PROPERTY(int numThreads READ getNumThreads WRITE setNumThreads)

    private:        
        VoxelTracer tracer;

        QUrl dataPath;
        qreal angleX;
        qreal angleY;
        qreal angleZ;                        

    public:
        explicit VoxelItem(QQuickItem* parent = 0);
        virtual void paint(QPainter* painter);

        void setDataPath(QUrl path);
        QUrl getDataPath() const;

        void setAngleX(qreal angle);
        qreal getAngleX() const;

        void setAngleY(qreal angle);
        qreal getAngleY() const;

        void setAngleZ(qreal angle);
        qreal getAngleZ() const;

        void setCameraDistance(qreal angle);
        qreal getCameraDistance() const;

        void setDraft(bool d);
        bool isDraft() const;

        void setBackgroundColor(const QColor& color);
        const QColor getBackgroundColor() const;

        void setTransparencyColor(const QColor& color);
        const QColor getTransparencyColor() const;

        void setTransparencyTolerance(qreal tolerance);
        qreal getTransparencyTolerance() const;

        void setVoxelSize(const QVector3D& voxelSize);
        const QVector3D getVoxelSize() const;

        void setNumThreads(int number);
        int getNumThreads() const;

    signals:
        void dataChanged();

    public slots:
};

class VoxelCanvas : public Canvas {
    private:
        QPainter* painter;

    public:
        VoxelCanvas(QPainter* p) : painter(p) {}
        int width() const override { return painter->viewport().width(); }
        int height() const override { return painter->viewport().height(); }
        void draw(unsigned char* pixels) override {
            painter->drawImage(0, 0, QImage(
                pixels, width(), height(), width()*3, QImage::Format_RGB888)
            );
        }
};

#endif // VOXELITEM_H
