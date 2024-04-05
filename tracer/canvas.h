#ifndef CANVAS_H
#define CANVAS_H

#include "../math/vector3.h"

class Canvas
{
    public:
        virtual int width() const = 0;
        virtual int height() const = 0;
        virtual void draw(unsigned char* pixels) = 0;
        virtual ~Canvas() {}
};

#endif // CANVAS_H
