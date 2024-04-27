#include "Bar.h"

void Bar::create()
{
	int i;
	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fLength / 2, 0, -fLongWidth / 2);
	pt[1].set(fLength / 2, 0, -fLongWidth / 2);
	pt[2].set(fLength / 2, 0, fLongWidth / 2);
	pt[3].set(-fLength / 2, 0, fLongWidth / 2);

	pt[4].set(-fLength / 2, fHeight, fShortWidth / 2);
	pt[5].set(fLength / 2, fHeight, fShortWidth / 2);
	pt[6].set(fLength / 2, fHeight, -fShortWidth / 2);
	pt[7].set(-fLength / 2, fHeight, -fShortWidth / 2);

	numFaces = 6;
	face = new Face[numFaces];

	// Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 3;
	face[0].vert[2].vertIndex = 4;
	face[0].vert[3].vertIndex = 7;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;
	// Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[0].nVerts];
	face[1].vert[0].vertIndex = 2;
	face[1].vert[1].vertIndex = 1;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[3].vertIndex = 5;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;
	// Top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[0].nVerts];
	face[2].vert[0].vertIndex = 4;
	face[2].vert[1].vertIndex = 5;
	face[2].vert[2].vertIndex = 6;
	face[2].vert[3].vertIndex = 7;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;
	// Bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[0].nVerts];
	face[3].vert[0].vertIndex = 3;
	face[3].vert[1].vertIndex = 2;
	face[3].vert[2].vertIndex = 1;
	face[3].vert[3].vertIndex = 0;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;
	// Near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[0].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 2;
	face[4].vert[3].vertIndex = 3;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;
	// Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[0].nVerts];
	face[5].vert[0].vertIndex = 7;
	face[5].vert[1].vertIndex = 6;
	face[5].vert[2].vertIndex = 1;
	face[5].vert[3].vertIndex = 0;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}

void Bar::Draw()
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