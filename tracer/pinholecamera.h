#ifndef PINHOLECAMERA_H
#define PINHOLECAMERA_H

#include "../math/Ray.h"
#include "../math/vector2.h"
#include "../math/vector3.h"
#include "../math/matrix4.h"
#include "../math/UVW.h"

class PinholeCamera
{
private:
    math::Vector3 position;
    math::Vector3 look;
    math::Vector3 up;
    float viewPlaneDistance;

    math::UVW* uvw;
    void updateUVW();

public:
    PinholeCamera(const math::Vector3& eye, const math::Vector3& look = math::Vector3(0, 0, 0),
                  const math::Vector3& up = math::Vector3(0,1,0), float viewPlaneDist=2000.0f);

    void setPosition(const math::Vector3& eye);
    const math::Vector3& getPosition() const;

    void setLook(const math::Vector3& positionToLook);
    const math::Vector3& getLook() const;

    void setUp(const math::Vector3& upDirection);
    const math::Vector3& getUp() const;

    math::Ray createRay(int x, int y) const;
    ~PinholeCamera();
};

#endif // PINHOLECAMERA_H
