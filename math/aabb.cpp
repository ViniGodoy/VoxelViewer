#include "aabb.h"

#include "vector3.h"
#include <assert.h>

#include <QDebug>

using namespace math;

float AABB::K_EPSILON = 0.1f;

AABB::AABB(const Vector3 &_p0, const Vector3 _p1)
    : p0(_p0), p1(_p1)
{
    assert(p0.x() < p1.x());
    assert(p0.y() < p1.y());
    assert(p0.z() < p1.z());
}

AABB::AABB(float x, float y, float z)
    : p0(x, y, z), p1(x+1, y+1, z+1)
{
}

bool AABB::hit(const Ray &ray, Vector3 &normal, float &dist, Vector3 &point, Vector3 &dir) const
{
    double ox = ray.getOrigin().x();
    double oy = ray.getOrigin().y();
    double oz = ray.getOrigin().z();

    double dx = ray.getDirection().x();
    double dy = ray.getDirection().y();
    double dz = ray.getDirection().z();

    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;

    double a = 1.0 / dx;
    if (a >= 0) {
        tx_min = (p0.x() - ox) * a;
        tx_max = (p1.x() - ox) * a;
    } else {
        tx_min = (p1.x() - ox) * a;
        tx_max = (p0.x() - ox) * a;
    }

    double b = 1.0 / dy;
    if (b >= 0) {
        ty_min = (p0.y() - oy) * b;
        ty_max = (p1.y() - oy) * b;
    } else {
        ty_min = (p1.y() - oy) * b;
        ty_max = (p0.y() - oy) * b;
    }

    double c = 1.0 / dz;
    if (c >= 0) {
        tz_min = (p0.z() - oz) * c;
        tz_max = (p1.z() - oz) * c;
    } else {
        tz_min = (p1.z() - oz) * c;
        tz_max = (p0.z() - oz) * c;
    }

    //Find the largest entering value
    Face faceIn;
    double t0;

    if (tx_min > ty_min) {
        t0 = tx_min;
        faceIn = a >= 0 ? LEFT : RIGHT;
    } else {
        t0 = ty_min;
        faceIn = b >= 0 ? BOTTOM : TOP;
    }
    if (tz_min > t0) {
        t0 = tz_min;
        faceIn = c >= 0 ? BACK : FRONT;
    }

    //Find the smallest exiting value
    double t1;
    Face faceOut;
    if (tx_max < ty_max) {
        t1 = tx_max;
        faceOut = a >= 0 ? RIGHT : LEFT;
    } else {
        t1 = ty_max;
        faceOut = b >= 0 ? TOP : BOTTOM;
    }
    if (tz_max < t1) {
        t1 = tz_max;
        faceOut = c >= 0 ? FRONT : BACK;
    }

    if (t0 < t1 && t1 > K_EPSILON) {
        if (t0 > K_EPSILON) {
            dist = (float) t0;
            normal = getNormal(faceIn);
        } else {
            dist = (float) t1;
            normal = getNormal(faceOut);
        }

        dir = ray.getDirection();
        point = ray.pointAt(dist) + dir * 0.01;
        return true;
    }

    return false;
}

bool AABB::contains(Vector3 &p) const
{
    return p.x() >= p0.x() && p.x() < p1.x() &&
            p.y() >= p0.y() && p.y() < p1.y() &&
            p.z() >= p0.z() && p.z() < p1.z();
}

const Vector3&AABB::getP0() const
{
    return p0;
}

const Vector3&AABB::getP1() const
{
    return p1;
}

float AABB::getWidth() const
{
    return p1.x() - p0.x();
}

float AABB::getHeight() const
{
    return p1.y() - p0.y();
}

float AABB::getDepth() const
{
    return p1.z() - p0.z();
}


Vector3 AABB::getNormal(Face face) const {
    switch (face) {
        case LEFT:
            return Vector3(-1, 0, 0);
        case BOTTOM:
            return Vector3(0, -1, 0);
        case BACK:
            return Vector3(0, 0, -1);
        case RIGHT:
            return Vector3(1, 0, 0);
        case TOP:
            return Vector3(0, 1, 0);
        case FRONT:
            return Vector3(0, 0, 1);
    }
    return Vector3(0, 0, 0);
}
