#ifndef RAY_H
#define RAY_H

#include "../math/vector3.h"

namespace math
{
    class Ray
    {
        private:
            math::Vector3 origin;
            math::Vector3 direction;

        public:
            Ray();

            explicit Ray(const math::Vector3 &o, const math::Vector3 &d);
            const math::Vector3& getOrigin() const;
            const math::Vector3& getDirection() const;
            math::Vector3 pointAt(float dist) const;
    };
}
#endif // RAY_H
