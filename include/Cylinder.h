#include "Mesh.h"

class Cylinder : public Mesh {
    public: 
        int nSegment;
        float fHeight;
        float fRadius;
        Cylinder(int nSegment, float fHeight, float fRadius) : nSegment(nSegment), fHeight(fHeight), fRadius(fRadius) {};
        
        void create();
        void create_alpha(float alpha);
        void Draw();
};