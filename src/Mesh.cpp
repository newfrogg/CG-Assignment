
#include "Mesh.h"
#include <math.h>
#include <iostream>
#define PI 3.1415926
#define COLORNUM 14

float ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, {0.9, 0.9, 0.9}, {1.0, 0.5, 0.5}, {0.5, 1.0, 0.5}, {0.5, 0.5, 1.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
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
	Mesh::CalculateFacesNorm();
}

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

void Mesh::CreateCube(float fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);

	numFaces = 6;
	face = new Face[numFaces];

	// Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	// Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	// top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	// bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	// near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	// Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

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

void Mesh::CreateTrapezium(float fHeight, float fShortWidth, float fLongWidth, float fLength)
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
	Mesh::CalculateFacesNorm();

}

// void Mesh::CreateHandle(float fLengthX, float fLengthZ, float fHeight, float fWidthX, float fWidthZ, float fRadiusX, float fRadiusY, float fRadiusZ)
// {
// 	int nSegmentX = 20;
// 	int nSegmentY = 20;
// 	int nSegmentZ = 10;
// 	float x, y, z;
// 	int i;
// 	int idx;
// 	numVerts = 16 + 2 * (1 + nSegmentZ) + 2;
// 	pt = new Point3[numVerts];
// 	pt[0].set(-fLengthX, 0, -fWidthX / 2);
// 	pt[1].set(-fLengthX, 0, fWidthX / 2);
// 	pt[2].set(-fWidthZ / 2, 0, fWidthX / 2);
// 	pt[3].set(-fWidthZ / 2, 0, fLengthZ);
// 	pt[4].set(fWidthZ / 2, 0, fLengthZ);
// 	pt[5].set(fWidthZ / 2, 0, fWidthX / 2);
// 	pt[6].set(fLengthX, 0, fWidthX / 2);
// 	pt[7].set(fLengthX, 0, -fWidthX / 2);

// 	pt[8].set(-fLengthX, fHeight, -fWidthX / 2);
// 	pt[9].set(-fLengthX, fHeight, fWidthX / 2);
// 	pt[10].set(-fWidthZ / 2, fHeight, fWidthX / 2);
// 	pt[11].set(-fWidthZ / 2, fHeight, fLengthZ);
// 	pt[12].set(fWidthZ / 2, fHeight, fLengthZ);
// 	pt[13].set(fWidthZ / 2, fHeight, fWidthX / 2);
// 	pt[14].set(fLengthX, fHeight, fWidthX / 2);
// 	pt[15].set(fLengthX, fHeight, -fWidthX / 2);

// 	// Extension Z
// 	float fAngleZ = -PI / nSegmentZ;
// 	pt[16].set(0, 0, fLengthZ);
// 	for (i = 0; i < nSegmentZ + 1; i++)
// 	{
// 		x = fRadiusZ * cos(fAngleZ * i);
// 		z = -fRadiusZ * sin(fAngleZ * i) + fLengthZ;
// 		y = 0;
// 		pt[16 + i + 1].set(x, y, z);
// 		// printf("x = %f, y = %f, z = %f \n", x, y, z);
// 		y = fHeight;
// 		// printf("x = %f, y = %f, z = %f \n", x, y, z);
// 		pt[16 + i + 1 + nSegmentZ].set(x, y, z);
// 	}
// 	pt[18 + 2 * nSegmentZ - 1 + 2].set(0, fHeight, fLengthZ);

// 	numFaces = 13 + 3 * nSegmentZ;
// 	face = new Face[numFaces];

// 	// NrBox
// 	{
// 		// Left face
// 		face[0].nVerts = 4;
// 		face[0].vert = new VertexID[face[0].nVerts];
// 		face[0].vert[0].vertIndex = 2;
// 		face[0].vert[1].vertIndex = 3;
// 		face[0].vert[2].vertIndex = 11;
// 		face[0].vert[3].vertIndex = 10;
// 		for (i = 0; i < face[0].nVerts; i++)
// 			face[0].vert[i].colorIndex = 0;

// 		// Right face
// 		face[1].nVerts = 4;
// 		face[1].vert = new VertexID[face[1].nVerts];
// 		face[1].vert[0].vertIndex = 4;
// 		face[1].vert[1].vertIndex = 5;
// 		face[1].vert[2].vertIndex = 13;
// 		face[1].vert[3].vertIndex = 12;
// 		for (i = 0; i < face[1].nVerts; i++)
// 			face[1].vert[i].colorIndex = 1;

// 		// top face
// 		face[2].nVerts = 4;
// 		face[2].vert = new VertexID[face[2].nVerts];
// 		face[2].vert[0].vertIndex = 10;
// 		face[2].vert[1].vertIndex = 11;
// 		face[2].vert[2].vertIndex = 12;
// 		face[2].vert[3].vertIndex = 13;
// 		for (i = 0; i < face[2].nVerts; i++)
// 			face[2].vert[i].colorIndex = 2;

// 		// bottom face
// 		face[3].nVerts = 4;
// 		face[3].vert = new VertexID[face[3].nVerts];
// 		face[3].vert[0].vertIndex = 2;
// 		face[3].vert[1].vertIndex = 3;
// 		face[3].vert[2].vertIndex = 4;
// 		face[3].vert[3].vertIndex = 5;
// 		for (i = 0; i < face[3].nVerts; i++)
// 			face[3].vert[i].colorIndex = 3;

// 		// near face
// 		face[4].nVerts = 4;
// 		face[4].vert = new VertexID[face[4].nVerts];
// 		face[4].vert[0].vertIndex = 3;
// 		face[4].vert[1].vertIndex = 4;
// 		face[4].vert[2].vertIndex = 12;
// 		face[4].vert[3].vertIndex = 11;
// 		for (i = 0; i < face[4].nVerts; i++)
// 			face[4].vert[i].colorIndex = 4;

// 		// Far face
// 		face[5].nVerts = 4;
// 		face[5].vert = new VertexID[face[5].nVerts];
// 		face[5].vert[0].vertIndex = 2;
// 		face[5].vert[1].vertIndex = 5;
// 		face[5].vert[2].vertIndex = 13;
// 		face[5].vert[3].vertIndex = 10;
// 		for (i = 0; i < face[5].nVerts; i++)
// 			face[5].vert[i].colorIndex = 5;
// 	}

// 	// FrBox
// 	{
// 		// Left face
// 		face[6].nVerts = 4;
// 		face[6].vert = new VertexID[face[6].nVerts];
// 		face[6].vert[0].vertIndex = 0;
// 		face[6].vert[1].vertIndex = 1;
// 		face[6].vert[2].vertIndex = 9;
// 		face[6].vert[3].vertIndex = 8;
// 		for (i = 0; i < face[6].nVerts; i++)
// 			face[6].vert[i].colorIndex = 0;

// 		// Right face
// 		face[7].nVerts = 4;
// 		face[7].vert = new VertexID[face[7].nVerts];
// 		face[7].vert[0].vertIndex = 7;
// 		face[7].vert[1].vertIndex = 6;
// 		face[7].vert[2].vertIndex = 14;
// 		face[7].vert[3].vertIndex = 15;
// 		for (i = 0; i < face[7].nVerts; i++)
// 			face[7].vert[i].colorIndex = 1;

// 		// top face
// 		face[8].nVerts = 4;
// 		face[8].vert = new VertexID[face[8].nVerts];
// 		face[8].vert[0].vertIndex = 8;
// 		face[8].vert[1].vertIndex = 9;
// 		face[8].vert[2].vertIndex = 14;
// 		face[8].vert[3].vertIndex = 15;
// 		for (i = 0; i < face[8].nVerts; i++)
// 			face[8].vert[i].colorIndex = 2;

// 		// bottom face
// 		face[9].nVerts = 4;
// 		face[9].vert = new VertexID[face[9].nVerts];
// 		face[9].vert[0].vertIndex = 0;
// 		face[9].vert[1].vertIndex = 1;
// 		face[9].vert[2].vertIndex = 6;
// 		face[9].vert[3].vertIndex = 7;
// 		for (i = 0; i < face[9].nVerts; i++)
// 			face[9].vert[i].colorIndex = 3;

// 		// near face 1
// 		face[10].nVerts = 4;
// 		face[10].vert = new VertexID[face[10].nVerts];
// 		face[10].vert[0].vertIndex = 1;
// 		face[10].vert[1].vertIndex = 2;
// 		face[10].vert[2].vertIndex = 10;
// 		face[10].vert[3].vertIndex = 9;
// 		for (i = 0; i < face[10].nVerts; i++)
// 			face[10].vert[i].colorIndex = 4;

// 		// near face 2
// 		face[11].nVerts = 4;
// 		face[11].vert = new VertexID[face[11].nVerts];
// 		face[11].vert[0].vertIndex = 5;
// 		face[11].vert[1].vertIndex = 6;
// 		face[11].vert[2].vertIndex = 14;
// 		face[11].vert[3].vertIndex = 13;
// 		for (i = 0; i < face[11].nVerts; i++)
// 			face[11].vert[i].colorIndex = 4;

// 		// Far face
// 		face[12].nVerts = 4;
// 		face[12].vert = new VertexID[face[12].nVerts];
// 		face[12].vert[0].vertIndex = 0;
// 		face[12].vert[1].vertIndex = 7;
// 		face[12].vert[2].vertIndex = 15;
// 		face[12].vert[3].vertIndex = 8;
// 		for (i = 0; i < face[12].nVerts; i++)
// 			face[12].vert[i].colorIndex = 5;
// 	}

// 	// ExtensionZ
// 	{
// 		idx = 14;
// 		for (i = 0; i < nSegmentZ; i++)
// 		{
// 			face[idx].nVerts = 3;
// 			face[idx].vert = new VertexID[face[idx].nVerts];
// 			face[idx].vert[0].vertIndex = 16;
// 			if (i < nSegmentZ - 1)
// 				face[idx].vert[1].vertIndex = 16 + i + 2;
// 			else
// 				face[idx].vert[1].vertIndex = 16 + 1;
// 			face[idx].vert[2].vertIndex = 16 + i + 1;
// 			idx++;
// 		}

// 		for (i = 0; i < nSegmentZ; i++)
// 		{
// 			face[idx].nVerts = 4;
// 			face[idx].vert = new VertexID[face[idx].nVerts];

// 			face[idx].vert[0].vertIndex = 16 + i + 1;
// 			if (i < nSegmentZ - 1)
// 				face[idx].vert[1].vertIndex = 16 + i + 2;
// 			else
// 				face[idx].vert[1].vertIndex = 16 + 1;
// 			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegmentZ;
// 			face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegmentZ;

// 			idx++;
// 		}

// 		// for (i = 0; i < nSegmentZ; i++)
// 		// {
// 		// 	face[idx].nVerts = 3;
// 		// 	face[idx].vert = new VertexID[face[idx].nVerts];
// 		// 	face[idx].vert[0].vertIndex = numVerts - 1;
// 		// 	if (i < nSegmentZ - 1)
// 		// 		face[idx].vert[2].vertIndex = 16 + i + 2 + nSegmentZ;
// 		// 	else
// 		// 		face[idx].vert[2].vertIndex =  16 + 1 + nSegmentZ;
// 		// 	face[idx].vert[1].vertIndex = 16 + i + 1 + nSegmentZ;
// 		// 	idx++;
// 		// }
// 	}
// }

void Mesh::CreatCrossBase(float fMainHeight, float fGrooveHeight, float fMainWidth, float fSubWidth, float fGrooveWidth, float fLength)
{

	if (fMainWidth - 2 * fSubWidth - fGrooveWidth > 0.1)
	{
		printf("[ERROR] SubWidth and GrooveWidth don't match with MainWidth\n");
		return;
	}
	////////////////////////////////////////////////////////////////////////
	//////  COMMON SIZE PARAMETERS
	////////////////////////////////////////////////////////////////////////

	//  local param
	float __main_h = fMainHeight;
	float __main_w = fMainWidth;
	float __main_l = fLength;

	float __groove_h = fGrooveHeight;
	float __groove_w = fGrooveWidth;

	float __sub_w = fSubWidth;

	// drivative param
	float half_groove_w = __groove_w / 2;

	// shape1 param (coordinator not actual sizes)
	//
	//
	//
	float s1_base = __groove_w / 2;
	float s1_l = __main_l + __groove_w / 2;
	float s1_w = __sub_w + __groove_w / 2;
	float s1_h = __main_h;

	// shape2 param
	//
	//
	//
	float s2_l = __main_l + __groove_w / 2;
	float s2_w = __groove_w / 2;
	float s2_h = __main_h / 2;

	// shape3 param
	//
	//
	//
	float s3_w = __groove_w / 2;
	float s3_l = __main_l + __groove_w / 2;
	float s3_h = __main_h / 2;

	int i;
	numVerts = 100;
	pt = new Point3[numVerts];

	/*
	Current index = 0
	*/
	// BOTTOM POINTS
	pt[0 + 0].set(-s1_l, 0, s1_base);
	pt[0 + 1].set(-s1_base, 0, s1_base);
	pt[0 + 2].set(-s1_base, 0, s1_l);
	pt[0 + 3].set(-s1_w, 0, s1_l);
	pt[0 + 4].set(-s1_w, 0, s1_w);
	pt[0 + 5].set(-s1_l, 0, s1_w);

	pt[6 * 1 + 0].set(+s1_l, 0, +s1_base);
	pt[6 * 1 + 1].set(+s1_base, 0, +s1_base);
	pt[6 * 1 + 2].set(+s1_base, 0, +s1_l);
	pt[6 * 1 + 3].set(+s1_w, 0, +s1_l);
	pt[6 * 1 + 4].set(+s1_w, 0, +s1_w);
	pt[6 * 1 + 5].set(+s1_l, 0, +s1_w);

	pt[6 * 2 + 0].set(+s1_l, 0, -s1_base);
	pt[6 * 2 + 1].set(+s1_base, 0, -s1_base);
	pt[6 * 2 + 2].set(+s1_base, 0, -s1_l);
	pt[6 * 2 + 3].set(+s1_w, 0, -s1_l);
	pt[6 * 2 + 4].set(+s1_w, 0, -s1_w);
	pt[6 * 2 + 5].set(+s1_l, 0, -s1_w);

	pt[6 * 3 + 0].set(-s1_l, 0, -s1_base);
	pt[6 * 3 + 1].set(-s1_base, 0, -s1_base);
	pt[6 * 3 + 2].set(-s1_base, 0, -s1_l);
	pt[6 * 3 + 3].set(-s1_w, 0, -s1_l);
	pt[6 * 3 + 4].set(-s1_w, 0, -s1_w);
	pt[6 * 3 + 5].set(-s1_l, 0, -s1_w);
	// TOP POINTS
	pt[6 * 4 + 0].set(-s1_l, s1_h, s1_base);
	pt[6 * 4 + 1].set(-s1_base, s1_h, s1_base);
	pt[6 * 4 + 2].set(-s1_base, s1_h, s1_l);
	pt[6 * 4 + 3].set(-s1_w, s1_h, s1_l);
	pt[6 * 4 + 4].set(-s1_w, s1_h, s1_w);
	pt[6 * 4 + 5].set(-s1_l, s1_h, s1_w);

	pt[6 * 5 + 0].set(+s1_l, s1_h, +s1_base);
	pt[6 * 5 + 1].set(+s1_base, s1_h, +s1_base);
	pt[6 * 5 + 2].set(+s1_base, s1_h, +s1_l);
	pt[6 * 5 + 3].set(+s1_w, s1_h, +s1_l);
	pt[6 * 5 + 4].set(+s1_w, s1_h, +s1_w);
	pt[6 * 5 + 5].set(+s1_l, s1_h, +s1_w);

	pt[6 * 6 + 0].set(+s1_l, s1_h, -s1_base);
	pt[6 * 6 + 1].set(+s1_base, s1_h, -s1_base);
	pt[6 * 6 + 2].set(+s1_base, s1_h, -s1_l);
	pt[6 * 6 + 3].set(+s1_w, s1_h, -s1_l);
	pt[6 * 6 + 4].set(+s1_w, s1_h, -s1_w);
	pt[6 * 6 + 5].set(+s1_l, s1_h, -s1_w);

	pt[6 * 7 + 0].set(-s1_l, s1_h, -s1_base);
	pt[6 * 7 + 1].set(-s1_base, s1_h, -s1_base);
	pt[6 * 7 + 2].set(-s1_base, s1_h, -s1_l);
	pt[6 * 7 + 3].set(-s1_w, s1_h, -s1_l);
	pt[6 * 7 + 4].set(-s1_w, s1_h, -s1_w);
	pt[6 * 7 + 5].set(-s1_l, s1_h, -s1_w);
	/*
	Current index = 48	=> round to 50
	*/
	// BOTTOM POINTS
	pt[50 + 4 * 0 + 0].set(-s2_w, 0, +s2_w);
	pt[50 + 4 * 0 + 1].set(+s2_w, 0, +s2_w);
	pt[50 + 4 * 0 + 2].set(+s2_w, 0, +s2_l);
	pt[50 + 4 * 0 + 3].set(-s2_w, 0, +s2_l);

	pt[50 + 4 * 1 + 0].set(-s2_w, 0, -s2_w);
	pt[50 + 4 * 1 + 1].set(+s2_w, 0, -s2_w);
	pt[50 + 4 * 1 + 2].set(+s2_w, 0, -s2_l);
	pt[50 + 4 * 1 + 3].set(-s2_w, 0, -s2_l);
	// TOP POINTS
	pt[50 + 4 * 2 + 0].set(-s2_w, s2_h, +s2_w);
	pt[50 + 4 * 2 + 1].set(+s2_w, s2_h, +s2_w);
	pt[50 + 4 * 2 + 2].set(+s2_w, s2_h, +s2_l);
	pt[50 + 4 * 2 + 3].set(-s2_w, s2_h, +s2_l);

	pt[50 + 4 * 3 + 0].set(-s2_w, s2_h, -s2_w);
	pt[50 + 4 * 3 + 1].set(+s2_w, s2_h, -s2_w);
	pt[50 + 4 * 3 + 2].set(+s2_w, s2_h, -s2_l);
	pt[50 + 4 * 3 + 3].set(-s2_w, s2_h, -s2_l);
	/*
	Current index = 66	=> round to 70
	*/
	// BOTTOM POINTS
	pt[70 + 4 * 0 + 0].set(-s3_w, 0, -s3_w);
	pt[70 + 4 * 0 + 1].set(-s3_w, 0, +s3_w);
	pt[70 + 4 * 0 + 2].set(-s3_l, 0, +s3_w);
	pt[70 + 4 * 0 + 3].set(-s3_l, 0, -s3_w);

	pt[70 + 4 * 1 + 0].set(+s3_w, 0, -s3_w);
	pt[70 + 4 * 1 + 1].set(+s3_w, 0, +s3_w);
	pt[70 + 4 * 1 + 2].set(+s3_l, 0, +s3_w);
	pt[70 + 4 * 1 + 3].set(+s3_l, 0, -s3_w);
	// TOP POINTS
	pt[70 + 4 * 2 + 0].set(-s3_w, s3_h, -s3_w);
	pt[70 + 4 * 2 + 1].set(-s3_w, s3_h, +s3_w);
	pt[70 + 4 * 2 + 2].set(-s3_l, s3_h, +s3_w);
	pt[70 + 4 * 2 + 3].set(-s3_l, s3_h, -s3_w);

	pt[70 + 4 * 3 + 0].set(+s3_w, s3_h, -s3_w);
	pt[70 + 4 * 3 + 1].set(+s3_w, s3_h, +s3_w);
	pt[70 + 4 * 3 + 2].set(+s3_l, s3_h, +s3_w);
	pt[70 + 4 * 3 + 3].set(+s3_l, s3_h, -s3_w);

	numFaces = 300;
	face = new Face[numFaces];

	int fei = 0;
	/*
	SHAPE 1 FACES
	*/
	for (int quarter_bot_and_top = 0; quarter_bot_and_top < 8; quarter_bot_and_top++)
	{
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 6 * quarter_bot_and_top + 0;
		face[fei].vert[1].vertIndex = 6 * quarter_bot_and_top + 1;
		face[fei].vert[2].vertIndex = 6 * quarter_bot_and_top + 4;
		face[fei].vert[3].vertIndex = 6 * quarter_bot_and_top + 5;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 6 * quarter_bot_and_top + 1;
		face[fei].vert[1].vertIndex = 6 * quarter_bot_and_top + 2;
		face[fei].vert[2].vertIndex = 6 * quarter_bot_and_top + 3;
		face[fei].vert[3].vertIndex = 6 * quarter_bot_and_top + 4;
		fei++;
	}
	for (int quarter = 0; quarter < 4; quarter++)
	{
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 6 * quarter + 0;
		face[fei].vert[1].vertIndex = 6 * quarter + 1;
		face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 1;
		face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 0;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 6 * quarter + 1;
		face[fei].vert[1].vertIndex = 6 * quarter + 2;
		face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 2;
		face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 1;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 6 * quarter + 2;
		face[fei].vert[1].vertIndex = 6 * quarter + 3;
		face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 3;
		face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 2;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 6 * quarter + 3;
		face[fei].vert[1].vertIndex = 6 * quarter + 4;
		face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 4;
		face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 3;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 6 * quarter + 4;
		face[fei].vert[1].vertIndex = 6 * quarter + 5;
		face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 5;
		face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 4;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 6 * quarter + 5;
		face[fei].vert[1].vertIndex = 6 * quarter + 0;
		face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 0;
		face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 5;
		fei++;
	}
	/*
	SHAPE 2 FACES
	*/
	for (int half_quarter_bot_and_top = 0; half_quarter_bot_and_top < 4; half_quarter_bot_and_top++)
	{
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 50 + 4 * half_quarter_bot_and_top + 0;
		face[fei].vert[1].vertIndex = 50 + 4 * half_quarter_bot_and_top + 1;
		face[fei].vert[2].vertIndex = 50 + 4 * half_quarter_bot_and_top + 2;
		face[fei].vert[3].vertIndex = 50 + 4 * half_quarter_bot_and_top + 3;
		fei++;
	}
	for (int half_quarter = 0; half_quarter < 2; half_quarter++)
	{
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 50 + 4 * half_quarter + 0;
		face[fei].vert[1].vertIndex = 50 + 4 * half_quarter + 1;
		face[fei].vert[2].vertIndex = 50 + 4 * (half_quarter + 2) + 1;
		face[fei].vert[3].vertIndex = 50 + 4 * (half_quarter + 2) + 0;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 50 + 4 * half_quarter + 1;
		face[fei].vert[1].vertIndex = 50 + 4 * half_quarter + 2;
		face[fei].vert[2].vertIndex = 50 + 4 * (half_quarter + 2) + 2;
		face[fei].vert[3].vertIndex = 50 + 4 * (half_quarter + 2) + 1;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 50 + 4 * half_quarter + 2;
		face[fei].vert[1].vertIndex = 50 + 4 * half_quarter + 3;
		face[fei].vert[2].vertIndex = 50 + 4 * (half_quarter + 2) + 3;
		face[fei].vert[3].vertIndex = 50 + 4 * (half_quarter + 2) + 2;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 50 + 4 * half_quarter + 3;
		face[fei].vert[1].vertIndex = 50 + 4 * half_quarter + 0;
		face[fei].vert[2].vertIndex = 50 + 4 * (half_quarter + 2) + 0;
		face[fei].vert[3].vertIndex = 50 + 4 * (half_quarter + 2) + 3;
		fei++;
	}
	/*
	SHAPE 3 FACES
	*/

	for (int half_quarter_bot_and_top = 0; half_quarter_bot_and_top < 4; half_quarter_bot_and_top++)
	{
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 70 + 4 * half_quarter_bot_and_top + 0;
		face[fei].vert[1].vertIndex = 70 + 4 * half_quarter_bot_and_top + 1;
		face[fei].vert[2].vertIndex = 70 + 4 * half_quarter_bot_and_top + 2;
		face[fei].vert[3].vertIndex = 70 + 4 * half_quarter_bot_and_top + 3;
		fei++;
	}
	for (int half_quarter = 0; half_quarter < 2; half_quarter++)
	{
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 70 + 4 * half_quarter + 0;
		face[fei].vert[1].vertIndex = 70 + 4 * half_quarter + 1;
		face[fei].vert[2].vertIndex = 70 + 4 * (half_quarter + 2) + 1;
		face[fei].vert[3].vertIndex = 70 + 4 * (half_quarter + 2) + 0;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 70 + 4 * half_quarter + 1;
		face[fei].vert[1].vertIndex = 70 + 4 * half_quarter + 2;
		face[fei].vert[2].vertIndex = 70 + 4 * (half_quarter + 2) + 2;
		face[fei].vert[3].vertIndex = 70 + 4 * (half_quarter + 2) + 1;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 70 + 4 * half_quarter + 2;
		face[fei].vert[1].vertIndex = 70 + 4 * half_quarter + 3;
		face[fei].vert[2].vertIndex = 70 + 4 * (half_quarter + 2) + 3;
		face[fei].vert[3].vertIndex = 70 + 4 * (half_quarter + 2) + 2;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[0].vertIndex = 70 + 4 * half_quarter + 3;
		face[fei].vert[1].vertIndex = 70 + 4 * half_quarter + 0;
		face[fei].vert[2].vertIndex = 70 + 4 * (half_quarter + 2) + 0;
		face[fei].vert[3].vertIndex = 70 + 4 * (half_quarter + 2) + 3;
		fei++;
	}

	/*
	ADDITION CENTER FOR TOP & BOTTOM SIDE
	*/
	face[fei].nVerts = 4;
	face[fei].vert = new VertexID[face[fei].nVerts];
	face[fei].vert[0].vertIndex = 70 + 0;
	face[fei].vert[1].vertIndex = 70 + 1;
	face[fei].vert[2].vertIndex = 70 + 5;
	face[fei].vert[3].vertIndex = 70 + 4;
	fei++;
	face[fei].nVerts = 4;
	face[fei].vert = new VertexID[face[fei].nVerts];
	face[fei].vert[0].vertIndex = 70 + 4 * 2 + 0;
	face[fei].vert[1].vertIndex = 70 + 4 * 2 + 1;
	face[fei].vert[2].vertIndex = 70 + 4 * 2 + 5;
	face[fei].vert[3].vertIndex = 70 + 4 * 2 + 4;

	Mesh::CalculateFacesNorm();
	printf("Num of faces: %d\n", fei);
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

void Mesh::CalculateFacesNorm() {
    float dx, dy, dz;
    int idx, next;
    for (int f = 0; f < numFaces; f++) {
        dx = 0;
        dy = 0;
        dz = 0;
        for (int v = 0; v < face[f].nVerts; v++) {
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
void Mesh::Draw() {
	for (int f = 0; f < numFaces; f++){
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++){
			int		iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

// Coloring Reference
// https://d2t1xqejof9utc.cloudfront.net/screenshots/pics/f64a9cd9f9c4e501e83abce6f95d9b40/large.jpg
// Color picker from image
// https://html-color.codes/image
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

void Mesh::DrawColorCrossBase()
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
			glColor3f(124.0f / 255, 124.0f / 255, 122.0f / 255);
			// if (f < 40)
			// 	glColor3f(0, 1, 0); // green
			// else
			// 	glColor3f(1, 0, 0); // red
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColorLatchCylinder()
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
			glColor3f(186.0f / 255, 189.0f / 255, 184.0f / 255);

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColorTieBar()
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
			glColor3f(228.0f / 255, 167.0f / 255, 83.0f / 255);

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColorSlider()
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
			glColor3f(254.0f / 255, 251.0f / 255, 41.0f / 255);

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}