#if !defined(_MESH_CLASS)
#define _MESH_CLASS

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
	void DrawColorCrossBase();
	void DrawColorLatchCylinder();
	void DrawColorTieBar();
	void DrawColorSlider();

	void CreateTetrahedron();
	void CreateCube(float fSize);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);

	void CreateCylinderModified(float center_x, float center_y, float center_z, int nSegment, float fHeight, float fRadius);
	/*
	Example: shape1.CreateTrapezium(1, 1 + 0.2, 2, 4);

	@param fShortWidth top of trapezium
	@param fLongWitdh bottom of trapezium
	*/
	void CreateTrapezium(float fHeight, float fShortWidth, float fLongWidth, float fLength);

	void CreateHandle(float fLengthX, float fLengthZ, float fHeight, float fWidthX, float fWidthZ, float fRadiusX, float fRadiusY, float fRadiusZ);
	/*
	@param fMainHeight
	@param fGrooveHeight
	@param fMainWidth
	@param fSubWidth
	@param fGrooveWidth
	@param fLength
	*/
	void CreatCrossBase(float fMainHeight, float fGrooveHeight, float fMainWidth, float fSubWidth, float fGrooveWidth, float fLength);
};

#endif