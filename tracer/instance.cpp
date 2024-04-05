#include "instance.h"

#include "../math/transform3d.h"
using namespace math::lh;

Instance::Instance(math::AABB &s, const math::Matrix4 &t, const math::Vector3 &c)
    : shape(s), transform(t), color(c)
{

}

bool Instance::hit(const math::Ray &ray, math::Vector3 &normal, float &dist, math::Vector3& point, math::Vector3& dir) const
{
    math::Matrix4 invTransform = math::inverse(transform);
    math::Ray invRay(
        transform3d(invTransform, ray.getOrigin()),
        transform3d(invTransform, ray.getDirection(), 0.0f));

    if (shape.hit(invRay, normal, dist, point, dir)) {
        //normal = transform3d(transform, normal, 0.0f).normalize();
        return true;
    }

    return false;
}

const math::AABB& Instance::getShape() const
{
    return shape;
}

void Instance::setTransform(const math::Matrix4 &t)
{
    transform = t;
}

const math::Matrix4 &Instance::getTransform() const
{
    return transform;
}

void Instance::setColor(const math::Vector3 &c)
{
    color = c;
}

const math::Vector3 &Instance::getColor() const
{
    return color;
}

