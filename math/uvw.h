#ifndef UVW_H
#define UVW_H

#include "vector3.h"
#include "vector2.h"

namespace math
{
    class UVW
    {
        private:
            Vector3 u;
            Vector3 v;
            Vector3 w;

        public:
            UVW(const Vector3& u, const Vector3& v, const Vector3& w);

            const Vector3& getU() const;
            const Vector3& getV() const;
            const Vector3& getW() const;
            Vector3 transform(const Vector3& vec) const;
            Vector3 transform(const Vector2& vec, float z) const;
        };
}

#endif // UVW_H
