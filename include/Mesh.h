#if !defined(_MESH_CLASS)
#define _MESH_CLASS
#define PI 3.1415926
#include "supportClass.h"
/*
Reference: https://www.instructables.com/Trammel-of-Archimedes-3D-Print/
*/
class VertexID
{
public:
	int vertIndex;
	int colorIndex;
};

class Face
{
public:
	int nVerts;
	VertexID *vert;
	Vector3 facenorm;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	// number of vertices
	int numVerts;
	Point3 *pt;
	// number of Faces
	int numFaces;
	Face *face;

public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
	void CalculateFacesNorm();
	void Draw();


	void CreateTetrahedron();


	void CreateCylinderModified(float center_x, float center_y, float center_z, int nSegment, float fHeight, float fRadius);
};

#endif