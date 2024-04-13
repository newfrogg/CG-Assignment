#include "Mesh.h"

class Base : public Mesh
{
public:
    float fMainHeight;
    float fGrooveHeight;
    float fMainWidth;
    float fSubWidth;
    float fGrooveWidth;
    float fLength;

    Base(float fMainHeight, float fGrooveHeight, float fMainWidth, float fSubWidth, float fGrooveWidth, float fLength)
        : fMainHeight(fMainHeight), fGrooveHeight(fGrooveHeight), fMainWidth(fMainWidth),
          fSubWidth(fSubWidth), fGrooveWidth(fGrooveWidth), fLength(fLength) {};

    void create();
    void Draw();
};