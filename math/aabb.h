#ifndef AABB_H
#define AABB_H

#include "ray.h"

namespace math
{
    enum Face
    {
        LEFT, RIGHT, BOTTOM, TOP, BACK, FRONT
    };

    class AABB
    {
        private:
            static float K_EPSILON;
            math::Vector3 p0;
            math::Vector3 p1;

            math::Vector3 getNormal(Face face) const;
        public:
            explicit AABB(const math::Vector3& p0, const math::Vector3 p1);
            explicit AABB(float x, float y, float z);

            virtual bool hit(const Ray& ray, math::Vector3& normal, float& dist, math::Vector3& point, math::Vector3& dir) const;
            virtual bool contains(math::Vector3& p) const;

            const math::Vector3& getP0() const;
            const math::Vector3& getP1() const;

            float getWidth() const;
            float getHeight() const;
            float getDepth() const;
    };
}
#endif // AABB_H
