#ifndef MOCKDATA_H
#define MOCKDATA_H

#include "data.h"

class MockData : public Data
{
    private:
        int w;
        int h;
        int d;

    public:
        MockData(int width, int height, int depth) :
            w(width), h(height), d(depth) {}

        virtual int getWidth() const override { return w; }
        virtual int getHeight() const override { return h; }
        virtual int getDepth() const override { return d; }
        virtual math::Vector3 get(int x, int y, int z) override {
            return (x < 0 || x >= getWidth()
                || y < 0 || y >= getHeight()
                || z < 0 || z >= getDepth())
                    ? math::Vector3()
                    : math::Vector3((x+1.0f) / w, (y+1.0f) / h, (z+1.0f) / d
            );
        }
};

#endif // MOCKDATA_H
