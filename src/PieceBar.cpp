#include "PieceBar.h"
#include <iostream>
using namespace std;

void PieceBar::create()
{
    int i;
    numVerts = 8 * 3;
    pt = new Point3[numVerts];
    // Left
    pt[4 * 0 + 0].set(-fMainWidth / 2, 0, 0);
    pt[4 * 0 + 1].set(-fMainWidth / 2, 0, fLength);
    pt[4 * 0 + 2].set(-fSubWidth / 2, 0, fLength);
    pt[4 * 0 + 3].set(-fSubWidth / 2, 0, 0);

    pt[4 * 1 + 0].set(-fMainWidth / 2, fHeight, 0);
    pt[4 * 1 + 1].set(-fMainWidth / 2, fHeight, fLength);
    pt[4 * 1 + 2].set(-fSubWidth / 2, fHeight, fLength);
    pt[4 * 1 + 3].set(-fSubWidth / 2, fHeight, 0);
    // Middle
    pt[4 * 2 + 0].set(-fSubWidth / 2, 0, 0);
    pt[4 * 2 + 1].set(-fSubWidth / 2, 0, fLength);
    pt[4 * 2 + 2].set(+fSubWidth / 2, 0, fLength);
    pt[4 * 2 + 3].set(+fSubWidth / 2, 0, 0);

    pt[4 * 3 + 0].set(-fSubWidth / 2, fHeight / 2, 0);
    pt[4 * 3 + 1].set(-fSubWidth / 2, fHeight / 2, fLength);
    pt[4 * 3 + 2].set(+fSubWidth / 2, fHeight / 2, fLength);
    pt[4 * 3 + 3].set(+fSubWidth / 2, fHeight / 2, 0);
    // Right
    pt[4 * 4 + 0].set(+fSubWidth / 2, 0, 0);
    pt[4 * 4 + 1].set(+fSubWidth / 2, 0, fLength);
    pt[4 * 4 + 2].set(+fMainWidth / 2, 0, fLength);
    pt[4 * 4 + 3].set(+fMainWidth / 2, 0, 0);

    pt[4 * 5 + 0].set(+fSubWidth / 2, fHeight, 0);
    pt[4 * 5 + 1].set(+fSubWidth / 2, fHeight, fLength);
    pt[4 * 5 + 2].set(+fMainWidth / 2, fHeight, fLength);
    pt[4 * 5 + 3].set(+fMainWidth / 2, fHeight, 0);

    numFaces = 6 * 3;
    face = new Face[numFaces];
    int idx = 0;
    for (int i = 0; i < 3; i++)
    {
        // Bottom face
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 4 * 2 * i + 0;
        face[idx].vert[1].vertIndex = 4 * 2 * i + 1;
        face[idx].vert[2].vertIndex = 4 * 2 * i + 2;
        face[idx].vert[3].vertIndex = 4 * 2 * i + 3;
        idx++;
        // Top face
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 4 * (2 * i + 1) + 0;
        face[idx].vert[1].vertIndex = 4 * (2 * i + 1) + 1;
        face[idx].vert[2].vertIndex = 4 * (2 * i + 1) + 2;
        face[idx].vert[3].vertIndex = 4 * (2 * i + 1) + 3;
        idx++;

        // Left face
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 4 * (2 * i + 1) + 0;
        face[idx].vert[1].vertIndex = 4 * (2 * i + 1) + 1;
        face[idx].vert[2].vertIndex = 4 * (2 * i) + 1;
        face[idx].vert[3].vertIndex = 4 * (2 * i) + 0;
        idx++;
        // Right face
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 4 * (2 * i + 1) + 3;
        face[idx].vert[1].vertIndex = 4 * (2 * i + 1) + 2;
        face[idx].vert[2].vertIndex = 4 * (2 * i) + 2;
        face[idx].vert[3].vertIndex = 4 * (2 * i) + 3;
        idx++;
        // Near face
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 4 * (2 * i + 1) + 1;
        face[idx].vert[1].vertIndex = 4 * (2 * i + 1) + 2;
        face[idx].vert[2].vertIndex = 4 * (2 * i) + 2;
        face[idx].vert[3].vertIndex = 4 * (2 * i) + 1;
        idx++;
        // Far face
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 4 * (2 * i + 1) + 0;
        face[idx].vert[1].vertIndex = 4 * (2 * i + 1) + 3;
        face[idx].vert[2].vertIndex = 4 * (2 * i) + 3;
        face[idx].vert[3].vertIndex = 4 * (2 * i) + 0;
        idx++;
    }
}

void PieceBar::Draw()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (int f = 0; f < numFaces; f++)
    {
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int iv = face[f].vert[v].vertIndex;
            glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}

void PieceBar::CalculateFacesNorm()
{
    float dx, dy, dz;
    int idx, next;
    for (int f = 0; f < numFaces; f++)
    {
        dx = 0;
        dy = 0;
        dz = 0;
        for (int v = 0; v < face[f].nVerts; v++)
        {
            idx = v;
            next = (idx + 1) % face[f].nVerts;

            int p1 = face[f].vert[idx].vertIndex;
            int p2 = face[f].vert[next].vertIndex;

            dx = dx + (pt[p1].y - pt[p2].y) * (pt[p1].z + pt[p2].z);
            dy = dy + (pt[p1].z - pt[p2].z) * (pt[p1].x + pt[p2].x);
            dz = dz + (pt[p1].x - pt[p2].x) * (pt[p1].y + pt[p2].y);
        }
        face[f].facenorm.set(dx, dy, dz);
        face[f].facenorm.normalize();
    }
}