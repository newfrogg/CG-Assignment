#include "Mesh.h"

class Bar : public Mesh
{
public:
    float fHeight;
    float fShortWidth;
    float fLongWidth;
    float fLength;

    Bar(float fHeight, float fShortWidth, float fLongWidth, float fLength) : fHeight(fHeight), fShortWidth(fShortWidth), fLongWidth(fLongWidth), fLength(fLength){};
    void create();
    void Draw();
};
