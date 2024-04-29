#include "Mesh.h"
#include "Cube.h"

class Tshape : public Mesh {
    public:
        int nSegment;
        float fLength;
        float fWidth;
        float fHeight;
        float fRadius;

        Tshape(int nSegment, float fLength, float fWidth, float fHeight, float fRadius) : nSegment(nSegment), fLength(fLength), fWidth(fWidth), fHeight(fHeight), fRadius(fRadius) {};
        void create();
        void Draw();
};