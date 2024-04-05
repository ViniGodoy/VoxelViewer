#ifndef VOXELTRACER_H
#define VOXELTRACER_H

#include "../math/ray.h"

#include "../math/matrix4.h"

#include "canvas.h"
#include "data.h"

#include <memory>
#include "../math/aabb.h"

class VoxelTracer;

class RenderTask
{
    private:
        int first;
        int last;
        int width;
        int height;
        VoxelTracer* tracer;
        unsigned char* pixels;

    public:
        explicit RenderTask(int first, int last, int w, int h, VoxelTracer* tracer, unsigned char* pixels);
        void operator()() const;
};

class VoxelTracer
{
    friend class RenderTask;

    private:                
        //Attributes
        std::shared_ptr<Data> data;
        float cameraDistance;
        bool draft;

        math::Vector3 backgroundColor;

        math::Vector3 transparencyColor;
        float transparencyTolerance;

        math::Vector3 voxelSize;
        int numThreads;

        //Private chaches
        math::AABB bounds;
        math::Matrix4 transform;

        //Private methods
        bool raytrace(const math::Ray& ray, math::Vector3& color, float& dist);
        math::AABB calculateBounds() const;
        math::AABB voxelFor(int x, int y, int z, int x2, int y2, int z2) const;
        math::AABB voxelFor(const math::Vector3& point) const;
        math::Vector3 pointFor(const math::Vector3 &approxPoint) const;

    public:
        VoxelTracer();
        void render(Canvas& canvas);

        void setTransform(const math::Matrix4& t);
        const math::Matrix4& getTransform() const;

        void setData(std::shared_ptr<Data> data);
        std::shared_ptr<Data> getData() const;

        void setCameraDistance(float distance);
        float getCameraDistance() const;

        void setDraft(bool draft);
        bool isDraft() const;

        void setBackgroundColor(const math::Vector3& color);
        const math::Vector3& getBackgroundColor() const;

        void setTransparencyColor(const math::Vector3& color);
        const math::Vector3& getTransparencyColor() const;

        void setTransparencyTolerance(float distance);
        float getTransparencyTolerance() const;

        void setVoxelSize(const math::Vector3& size);
        const math::Vector3& getVoxelSize() const;

        void setNumThreads(int number);
        int getNumThreads() const;
};


#endif // VOXELTRACER_H
