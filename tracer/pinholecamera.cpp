#include "pinholecamera.h"

#include "../math/vector2.h"

PinholeCamera::PinholeCamera(const math::Vector3 &eye, const math::Vector3 &look, const math::Vector3 &up, float viewPlaneDist)
    : position(eye), look(look), up(up), viewPlaneDistance(viewPlaneDist), uvw(nullptr)
{
    updateUVW();
}

void PinholeCamera::updateUVW()
{
    using namespace math;

    if (uvw) delete uvw;

    Vector3 w = (position - look).normalize();

    // take care of the singularity by hardwiring in specific camera orientations
    if (position.x() == look.x() && position.z() == look.z() && position.y() > look.y()) { // camera looking vertically down
        uvw = new UVW(
                Vector3(0, 0, 1),
                Vector3(1, 0, 0),
                Vector3(0, 1, 0));
        return;
    }

    if (position.x() == look.x() && position.z() == look.z() && position.y() < look.y()) { // camera looking vertically up
        uvw = new UVW(
                Vector3(1, 0, 0),
                Vector3(0, 0, 1),
                Vector3(0, -1, 0));
        return;
    }

    //Otherwise, calculate UVW
    Vector3 u = cross(up, w).normalize();
    Vector3 v = cross(w, u);

    uvw = new UVW(u, v, w);
}

void PinholeCamera::setPosition(const math::Vector3 &eye)
{
    position = eye;
    updateUVW();
}

const math::Vector3& PinholeCamera::getPosition() const
{
    return position;
}

void PinholeCamera::setLook(const math::Vector3 &positionToLook)
{
    look = positionToLook;
    updateUVW();
}

const math::Vector3& PinholeCamera::getLook() const
{
    return look;
}

void PinholeCamera::setUp(const math::Vector3 &upDirection)
{
    up = math::normalize(upDirection);
    updateUVW();
}

const math::Vector3 &PinholeCamera::getUp() const
{
    return up;
}

math::Ray PinholeCamera::createRay(int x, int y) const
{
    return math::Ray(getPosition(), uvw->transform(math::Vector2(x, y), -viewPlaneDistance).normalize());
}

PinholeCamera::~PinholeCamera()
{
    if (uvw) delete uvw;
}

