#include "Mesh.h"

class Cube : public Mesh
{
public:
    float fSize;
    Cube(float fSize) : fSize(fSize){};
    void create();
    void Draw();
};