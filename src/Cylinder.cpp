#include "Cylinder.h"

void Cylinder::create()
{
    numVerts = nSegment * 2 + 2;
    pt = new Point3[numVerts];

    int i;
    int idx;
    float fAngle = 2 * PI / nSegment;
    float x, y, z;

    pt[0].set(0, fHeight / 2, 0);
    // chi toi nsegment vi day la hinh cung kin (diem dau == diem cuoi)
    for (i = 0; i < nSegment; i++)
    {
        x = fRadius * cos(fAngle * i);
        z = fRadius * sin(fAngle * i);
        y = fHeight / 2;
        pt[i + 1].set(x, y, z);
        // printf("x = %f, y = %f, z = %f \n", x, y, z);

        y = -fHeight / 2;
        // printf("x = %f, y = %f, z = %f \n", x, y, z);
        pt[i + 1 + nSegment].set(x, y, z);
    }
    pt[numVerts - 1].set(0, -fHeight / 2, 0);

    numFaces = nSegment * 3;
    face = new Face[numFaces];

    idx = 0;
    for (i = 0; i < nSegment; i++)
    {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = 0;
        if (i < nSegment - 1)
            face[idx].vert[1].vertIndex = i + 2;
        else
            face[idx].vert[1].vertIndex = 1;
        face[idx].vert[2].vertIndex = i + 1;
        idx++;
    }

    for (i = 0; i < nSegment; i++)
    {
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = i + 1;
        if (i < nSegment - 1)
            face[idx].vert[1].vertIndex = i + 2;
        else
            face[idx].vert[1].vertIndex = 1;
        face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
        face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

        idx++;
    }

    for (i = 0; i < nSegment; i++)
    {
        face[idx].nVerts = 3;
        face[idx].vert = new VertexID[face[idx].nVerts];
        face[idx].vert[0].vertIndex = numVerts - 1;
        if (i < nSegment - 1)
            face[idx].vert[2].vertIndex = i + 2 + nSegment;
        else
            face[idx].vert[2].vertIndex = 1 + nSegment;
        face[idx].vert[1].vertIndex = i + 1 + nSegment;
        idx++;
    }
}

void Cylinder::Draw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			glColor3f(186.0f / 255, 189.0f / 255, 184.0f / 255);

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}