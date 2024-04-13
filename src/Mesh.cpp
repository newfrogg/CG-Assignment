
#include "Mesh.h"
#include <math.h>
#include <iostream>
#define PI 3.1415926
#define COLORNUM 14

// Coloring Reference
// https://d2t1xqejof9utc.cloudfront.net/screenshots/pics/f64a9cd9f9c4e501e83abce6f95d9b40/large.jpg
// Color picker from image
// https://html-color.codes/image

float ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, {0.9, 0.9, 0.9}, {1.0, 0.5, 0.5}, {0.5, 1.0, 0.5}, {0.5, 0.5, 1.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};

void Mesh::CreateCylinderModified(float center_x, float center_y, float center_z, int nSegment, float fHeight, float fRadius)
{
	////////////////////////////////////////////////////////////////////////
	//////  COMMON SIZE PARAMETERS
	////////////////////////////////////////////////////////////////////////
	float __center_x = center_x;
	float __center_y = center_y;
	float __center_z = center_z;

	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int i;
	int idx;
	float fAngle = 2 * PI / nSegment;
	float x, y, z;

	pt[0].set(__center_x, fHeight / 2 + __center_y, __center_z);
	// chi toi nsegment vi day la hinh cung kin (diem dau == diem cuoi)
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * cos(fAngle * i) + __center_x;
		z = fRadius * sin(fAngle * i) + __center_z;
		y = fHeight / 2 + __center_y;
		pt[i + 1].set(x, y, z);
		// printf("x = %f, y = %f, z = %f \n", x, y, z);

		y = -fHeight / 2 + __center_y;
		// printf("x = %f, y = %f, z = %f \n", x, y, z);
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(__center_x, -fHeight / 2 + __center_y, __center_z);

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
	Mesh::CalculateFacesNorm();
}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts = 4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces = 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	Mesh::CalculateFacesNorm();
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::CalculateFacesNorm()
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
void Mesh::Draw()
{
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

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int ic = face[f].vert[v].colorIndex;

			ic = f % COLORNUM;
			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}
