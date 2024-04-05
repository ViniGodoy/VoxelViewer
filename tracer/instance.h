#ifndef INSTANCE_H
#define INSTANCE_H

#include "../math/matrix4.h"
#include "../math/aabb.h"

class Instance
{
    private:
        math::AABB& shape;
        math::Matrix4 transform;
        math::Vector3 color;

    public:
        Instance(math::AABB& s, const math::Matrix4& t = math::Matrix4::newIdentity(), const math::Vector3& color = math::Vector3(1, 0, 0));
        virtual bool hit(const math::Ray& ray, math::Vector3& normal, float& dist, math::Vector3& point, math::Vector3& dir) const;

        const math::AABB& getShape() const;

        void setTransform(const math::Matrix4& transform);
        const math::Matrix4& getTransform() const;

        void setColor(const math::Vector3& color);
        const math::Vector3 &getColor() const;
};

#endif // INSTANCE_H
