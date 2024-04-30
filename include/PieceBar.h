#include "Mesh.h"

class PieceBar : public Mesh
{
public:
    float fHeight;
    float fMainWidth;
    float fSubWidth;
    float fLength;

    PieceBar(float fHeight, float fMainWidth, float fSubWidth, float fLength) : fHeight(fHeight), fMainWidth(fMainWidth), fSubWidth(fSubWidth), fLength(fLength){};
    void create();
    void CalculateFacesNorm();
    void Draw();
};