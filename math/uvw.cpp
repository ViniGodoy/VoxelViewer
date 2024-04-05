#include "uvw.h"

using namespace math;

UVW::UVW(const Vector3 &u, const Vector3 &v, const Vector3 &w) : u(u), v(v), w(w)
{
}

const Vector3 &UVW::getU() const
{
    return u;
}

const Vector3 &UVW::getV() const
{
    return v;
}

const Vector3 &UVW::getW() const
{
    return w;
}

Vector3 UVW::transform(const Vector3 &vec) const
{
    return u * vec.x() + v * vec.y() + w * vec.z();
}

Vector3 UVW::transform(const Vector2 &vec, float z) const
{
    return u * vec.x() + v * vec.y() + w * z;
}


