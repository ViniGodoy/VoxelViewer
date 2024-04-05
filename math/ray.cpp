#include "ray.h"

using namespace math;

Ray::Ray(const Vector3 &o, const Vector3 &d)
    : origin(o), direction(d)
{
}

const Vector3 &Ray::getOrigin() const
{
    return origin;
}

const Vector3 &Ray::getDirection() const
{
    return direction;
}

Vector3 Ray::pointAt(float dist) const
{
    return direction * dist + origin;
}
