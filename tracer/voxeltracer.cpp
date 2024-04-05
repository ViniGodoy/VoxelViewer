#include "voxeltracer.h"

#include "instance.h"

#include "../math/ray.h"
#include "../math/transform3d.h"
#include "tracer/pinholecamera.h"

#include <thread>
#include <future>

#include <QDebug>

VoxelTracer::VoxelTracer() :
    cameraDistance(2000.0f), draft(true), backgroundColor(0.345, 0.49, 0.4), transparencyTolerance(0.06f),
    voxelSize(1,1,1), numThreads(6), bounds(0,0,0), transform(math::Matrix4::newIdentity())
{
}

bool VoxelTracer::raytrace(const math::Ray &ray, math::Vector3 &color, float &dist)
{
    using namespace math;

    //Find the intersection point
    Instance areaInstance(bounds, transform);
    Vector3 normal;
    Vector3 point;
    Vector3 dir;
    float distance = -1;

    if (!areaInstance.hit(ray, normal, distance, point, dir)) {
        color = backgroundColor;
        return false;
    } else if (draft) {
        color = (Vector3(1,1,1) + normal) / 2;
        return true;
    }

    //Iterate over util leaving the voxel area or until hit
    Vector3 lastCoords(-10000000, -10000000, -10000000);

    while (bounds.contains(point))
    {
        Vector3 coords = pointFor(point);
        if (coords.x() == lastCoords.x() &&
            coords.y() == lastCoords.y() &&
            coords.z() == lastCoords.z())
        {
            point += dir;
            continue;
        }

        lastCoords = coords;
        AABB voxel = voxelFor(coords);
        Instance instance(voxel, transform, data->get(
                              static_cast<int>(coords.x()),
                              static_cast<int>(coords.y()),
                              static_cast<int>(coords.z())));

        bool transparent = math::distanceSqr(instance.getColor(), transparencyColor) <=
                transparencyTolerance * transparencyTolerance;

        if (!transparent && instance.hit(ray, normal, distance, point, dir))
        {
            color = instance.getColor();
            dist = distance;
            return true;
        }
        point += dir;
    }
    color = backgroundColor;
    return false;
}

math::AABB VoxelTracer::calculateBounds() const
{
    if (!data) {
        return math::AABB(0,0,0);
    }

    float hw = getVoxelSize().x() * data->getWidth() * 0.5f;
    float hh = getVoxelSize().y() * data->getHeight() * 0.5f;
    float hd = getVoxelSize().z() * data->getDepth() * 0.5f;
    return math::AABB(math::Vector3(-hw, -hh, -hd), math::Vector3(hw, hh, hd));
}

math::AABB VoxelTracer::voxelFor(int x, int y, int z, int x2, int y2, int z2) const
{
    return math::AABB(math::Vector3(x, y, z) * getVoxelSize() - bounds.getP1(),
                      math::Vector3(x2, y2, z2) * getVoxelSize() - bounds.getP1());
}

math::AABB VoxelTracer::voxelFor(const math::Vector3& point) const
{
    math::Vector3 p0 = point * getVoxelSize() - bounds.getP1();
    return math::AABB(p0, p0 + getVoxelSize());
}

math::Vector3 VoxelTracer::pointFor(const math::Vector3 &approxPoint) const
{
    int px = static_cast<int>((approxPoint.x() + bounds.getP1().x()) / getVoxelSize().x());
    int py = static_cast<int>((approxPoint.y() + bounds.getP1().y()) / getVoxelSize().y());
    int pz = static_cast<int>((approxPoint.z() + bounds.getP1().z()) / getVoxelSize().z());

    return math::Vector3(px, py, pz);
}

void VoxelTracer::render(Canvas &canvas)
{
    //Create scene image area
    unsigned char* pixels = new unsigned char[canvas.width() * canvas.height() * 3];
    memset(pixels, 0, canvas.width() * canvas.height() * 3);

    //Create the processing tasks
    std::vector<std::future<void> > tasks;
    float slice = static_cast<float>(canvas.height()) / numThreads;

    for (int i = 1; i <= numThreads; ++i) {
        int first = static_cast<int>((i-1) * slice);
        int last = static_cast<int>(i * slice);
        std::packaged_task<void()> task(RenderTask(first, last, canvas.width(), canvas.height(), this, pixels));
        tasks.push_back(task.get_future());
         std::thread(std::move(task)).detach();
    }

    //Wait for the result
    for (int i = 0; i < numThreads; ++i) {
        tasks[i].wait();
    }

    canvas.draw(pixels);
    delete [] pixels;
}

void VoxelTracer::setTransform(const math::Matrix4 &t)
{
    transform = t;
}

const math::Matrix4 &VoxelTracer::getTransform() const
{    
    return transform;
}

void VoxelTracer::setData(std::shared_ptr<Data>d)
{
    data = d;
    voxelSize = data ? data->getVoxelSize() : math::Vector3(1,1,1);
    bounds = calculateBounds();
}

std::shared_ptr<Data> VoxelTracer::getData() const
{
    return data;
}

void VoxelTracer::setCameraDistance(float distance)
{
    cameraDistance = distance;
}

float VoxelTracer::getCameraDistance() const
{
    return cameraDistance;
}

void VoxelTracer::setDraft(bool draft)
{
    this->draft = draft;
}

bool VoxelTracer::isDraft() const
{
    return draft;
}

void VoxelTracer::setBackgroundColor(const math::Vector3& color)
{
    backgroundColor = math::saturate(color);
}

const math::Vector3&VoxelTracer::getBackgroundColor() const
{
    return backgroundColor;
}

void VoxelTracer::setTransparencyColor(const math::Vector3& color)
{
    transparencyColor = math::saturate(color);
}

const math::Vector3&VoxelTracer::getTransparencyColor() const
{
    return transparencyColor;
}

void VoxelTracer::setTransparencyTolerance(float distance)
{
    transparencyTolerance = distance < 0 ? 0 : (distance > 1 ? 1 : distance);
}

float VoxelTracer::getTransparencyTolerance() const
{
    return transparencyTolerance;
}

const math::Vector3&VoxelTracer::getVoxelSize() const
{
    return voxelSize;
}

void VoxelTracer::setNumThreads(int number)
{
    numThreads = number < 1 ? 1 : number;
}

int VoxelTracer::getNumThreads() const
{
    return numThreads;
}

void VoxelTracer::setVoxelSize(const math::Vector3& size)
{
    float min = size.x();
    if (min > size.y()) min = size.y();
    if (min > size.z()) min = size.z();

    voxelSize = size / min;
    bounds = calculateBounds();
}



RenderTask::RenderTask(int f, int l, int w, int h, VoxelTracer* t, unsigned char* p)
    : first(f), last(l), width(w), height(h), tracer(t), pixels(p)
{
}

void RenderTask::operator() () const
{
    using namespace math;

    PinholeCamera camera(Vector3(0, 0, tracer->cameraDistance),
                         Vector3(0, 0, 0));
    int step = 1;//tracer->isDraft() ? 10 : 1;

    // render remaining lines
    for (int y = first; y < last; y+=step)
    {
        // render pixels for current line
        for (int x = 0; x < width; x+=step)
        {
            // fire primary ray
            Vector3 color;
            float dist;
            tracer->raytrace(camera.createRay(x - width * 0.5f, height * 0.5f - y), color, dist);

            int i = (y * width + x) * 3;
            pixels[i] = static_cast<unsigned char>(color.r() * 255.0f);
            pixels[i+1] = static_cast<unsigned char>(color.g() * 255.0f);
            pixels[i+2] = static_cast<unsigned char>(color.b() * 255.0f);
        }
    }
}
