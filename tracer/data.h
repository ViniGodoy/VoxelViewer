#ifndef DATA_H
#define DATA_H

#include "../math/vector3.h"

class Data
{
    public:
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual int getDepth() const = 0;
        virtual math::Vector3 get(int x, int y, int z) = 0;
        virtual math::Vector3 getVoxelSize() const { return math::Vector3(1,1,1); }
        virtual ~Data() {}
};

#endif // DATA_H
