#include <math.h>
#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

#define M_PI 3.14
#define DEG2RAD(x) (x * M_PI) / 180.0f
#define PI 3.1415926
#define COLORNUM 14

using namespace std;
// Support Class
#pragma region
class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	void set(Point3& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}
	void set(Color3& c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}
};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy)
	{
		x = xx;
		y = yy;
	} // constructor 2
	void set(float xx, float yy)
	{
		x = xx;
		y = yy;
	}
	float getX() { return x; }
	float getY() { return y; }
	void draw()
	{
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}

private:
	float x, y;
};
class IntRect
{
public:
	IntRect()
	{
		l = 0;
		r = 100;
		b = 0;
		t = 100;
	} // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void draw()
	{
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int getWidth() { return (r - l); }
	int getHeight() { return (t - b); }

private:
	int l, r, b, t;
};

class RealRect
{
public:
	RealRect()
	{
		l = 0;
		r = 100;
		b = 0;
		t = 100;
	} // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left;
		r = right;
		b = bottom;
		t = top;
	}
	float getWidth() { return (r - l); }
	float getHeight() { return (t - b); }
	void draw()
	{
		glRectf(l, b, r, t);
		glFlush();
	}; // draw this rectangle using OpenGL
private:
	float l, r, b, t;
};

class Vector3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	void flip()
	{
		x = -x;
		y = -y;
		z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx;
		y = dy;
		z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x * b.x + y * b.y + z * b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x * x + y * y + z * z);
	x = x / temp;
	y = y / temp;
	z = z / temp;
}
#pragma endregion
// Mesh
#pragma region

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
	VertexID* vert;
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
	Point3* pt;
	// number of Faces
	int numFaces;
	Face* face;

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
			//delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
	void CalculateFacesNorm();
	void Draw();
};
float ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, {0.9, 0.9, 0.9}, {1.0, 0.5, 0.5}, {0.5, 1.0, 0.5}, {0.5, 0.5, 1.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };

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

#pragma endregion
// Cylinder
#pragma region
class Cylinder : public Mesh
{
public:
	int nSegment;
	float fHeight;
	float fRadius;
	Cylinder(int nSegment, float fHeight, float fRadius) : nSegment(nSegment), fHeight(fHeight), fRadius(fRadius) {};

	void create();
	void create_alpha(float alpha);
	void create_compensation(float alpha);
	void Draw();
};

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

void Cylinder::create_alpha(float alpha)
{
	numVerts = (nSegment + 1) * 2 + 2;
	pt = new Point3[numVerts];
	int i;
	int idx;
	float fAngle = DEG2RAD(alpha) / (nSegment - 1);
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

void Cylinder::create_compensation(float alpha)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];
	int i;
	int idx;
	float fAngle = DEG2RAD(alpha) / nSegment;
	float x, y, z;

	pt[0].set(fRadius, fHeight / 2, fRadius);
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
	pt[numVerts - 1].set(fRadius, -fHeight / 2, fRadius);

	numFaces = (nSegment - 1) * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment - 1; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			continue;
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
			continue;
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
			continue;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}
}

void Cylinder::Draw()
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
#pragma endregion
// Base
#pragma region
class Base : public Mesh
{
public:
	float fMainHeight;
	float fGrooveHeight;
	float fMainWidth;
	float fSubWidth;
	float fGrooveWidth;
	float fLength;

	Base(float fMainHeight, float fGrooveHeight, float fMainWidth, float fSubWidth, float fGrooveWidth, float fLength)
		: fMainHeight(fMainHeight), fGrooveHeight(fGrooveHeight), fMainWidth(fMainWidth),
		fSubWidth(fSubWidth), fGrooveWidth(fGrooveWidth), fLength(fLength) {};

	void create();
	void Draw();
};
void Base::create()
{
	if (fMainWidth - 2 * fSubWidth - fGrooveWidth > 0.1)
	{
		// printf("[ERROR] SubWidth and GrooveWidth don't match with MainWidth\n");
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
		if (quarter_bot_and_top % 2)
		{
			face[fei].vert[0].vertIndex = 6 * quarter_bot_and_top + 0;
			face[fei].vert[1].vertIndex = 6 * quarter_bot_and_top + 1;
			face[fei].vert[2].vertIndex = 6 * quarter_bot_and_top + 4;
			face[fei].vert[3].vertIndex = 6 * quarter_bot_and_top + 5;
		}
		else
		{
			face[fei].vert[0].vertIndex = 6 * quarter_bot_and_top + 5;
			face[fei].vert[1].vertIndex = 6 * quarter_bot_and_top + 4;
			face[fei].vert[2].vertIndex = 6 * quarter_bot_and_top + 1;
			face[fei].vert[3].vertIndex = 6 * quarter_bot_and_top + 0;
		}

		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		if (quarter_bot_and_top % 2)
		{
			face[fei].vert[0].vertIndex = 6 * quarter_bot_and_top + 1;
			face[fei].vert[1].vertIndex = 6 * quarter_bot_and_top + 2;
			face[fei].vert[2].vertIndex = 6 * quarter_bot_and_top + 3;
			face[fei].vert[3].vertIndex = 6 * quarter_bot_and_top + 4;
		}
		else
		{
			face[fei].vert[0].vertIndex = 6 * quarter_bot_and_top + 4;
			face[fei].vert[1].vertIndex = 6 * quarter_bot_and_top + 3;
			face[fei].vert[2].vertIndex = 6 * quarter_bot_and_top + 2;
			face[fei].vert[3].vertIndex = 6 * quarter_bot_and_top + 1;
		}
		fei++;
	}
	for (int quarter = 0; quarter < 4; quarter++)
	{
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		if (quarter == 0 || quarter == 3)
		{
			face[fei].vert[3].vertIndex = 6 * quarter + 0;
			face[fei].vert[2].vertIndex = 6 * quarter + 1;
			face[fei].vert[1].vertIndex = 6 * (quarter + 4) + 1;
			face[fei].vert[0].vertIndex = 6 * (quarter + 4) + 0;
		}
		else
		{
			face[fei].vert[0].vertIndex = 6 * quarter + 0;
			face[fei].vert[1].vertIndex = 6 * quarter + 1;
			face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 1;
			face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 0;
		}
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		if (quarter != 0 && quarter != 1)
		{
			face[fei].vert[3].vertIndex = 6 * quarter + 1;
			face[fei].vert[2].vertIndex = 6 * quarter + 2;
			face[fei].vert[1].vertIndex = 6 * (quarter + 4) + 2;
			face[fei].vert[0].vertIndex = 6 * (quarter + 4) + 1;
		}
		else
		{
			face[fei].vert[0].vertIndex = 6 * quarter + 1;
			face[fei].vert[1].vertIndex = 6 * quarter + 2;
			face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 2;
			face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 1;
		}
		fei++;
		face[fei].nVerts = 4;
		if (quarter % 2)
		{
			face[fei].vert = new VertexID[face[fei].nVerts];
			face[fei].vert[3].vertIndex = 6 * quarter + 2;
			face[fei].vert[2].vertIndex = 6 * quarter + 3;
			face[fei].vert[1].vertIndex = 6 * (quarter + 4) + 3;
			face[fei].vert[0].vertIndex = 6 * (quarter + 4) + 2;
		}
		else
		{
			face[fei].vert = new VertexID[face[fei].nVerts];
			face[fei].vert[0].vertIndex = 6 * quarter + 2;
			face[fei].vert[1].vertIndex = 6 * quarter + 3;
			face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 3;
			face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 2;
		}
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		if (quarter == 0 || quarter == 1)
		{
			face[fei].vert[3].vertIndex = 6 * quarter + 3;
			face[fei].vert[2].vertIndex = 6 * quarter + 4;
			face[fei].vert[1].vertIndex = 6 * (quarter + 4) + 4;
			face[fei].vert[0].vertIndex = 6 * (quarter + 4) + 3;
		}
		else
		{
			face[fei].vert[0].vertIndex = 6 * quarter + 3;
			face[fei].vert[1].vertIndex = 6 * quarter + 4;
			face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 4;
			face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 3;
		}
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		if (quarter == 1 || quarter == 2)
		{
			face[fei].vert[3].vertIndex = 6 * quarter + 4;
			face[fei].vert[2].vertIndex = 6 * quarter + 5;
			face[fei].vert[1].vertIndex = 6 * (quarter + 4) + 5;
			face[fei].vert[0].vertIndex = 6 * (quarter + 4) + 4;
		}
		else
		{
			face[fei].vert[0].vertIndex = 6 * quarter + 4;
			face[fei].vert[1].vertIndex = 6 * quarter + 5;
			face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 5;
			face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 4;
		}
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		if (quarter == 0 || quarter == 1)
		{
			face[fei].vert[3].vertIndex = 6 * quarter + 5;
			face[fei].vert[2].vertIndex = 6 * quarter + 0;
			face[fei].vert[1].vertIndex = 6 * (quarter + 4) + 0;
			face[fei].vert[0].vertIndex = 6 * (quarter + 4) + 5;
		}
		else
		{
			face[fei].vert[0].vertIndex = 6 * quarter + 5;
			face[fei].vert[1].vertIndex = 6 * quarter + 0;
			face[fei].vert[2].vertIndex = 6 * (quarter + 4) + 0;
			face[fei].vert[3].vertIndex = 6 * (quarter + 4) + 5;
		}
		fei++;
	}
	/*
	SHAPE 2 FACES
	*/
	for (int half_quarter_bot_and_top = 0; half_quarter_bot_and_top < 4; half_quarter_bot_and_top++)
	{
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		if (half_quarter_bot_and_top % 2 == 1)
		{
			face[fei].vert[0].vertIndex = 50 + 4 * half_quarter_bot_and_top + 0;
			face[fei].vert[1].vertIndex = 50 + 4 * half_quarter_bot_and_top + 1;
			face[fei].vert[2].vertIndex = 50 + 4 * half_quarter_bot_and_top + 2;
			face[fei].vert[3].vertIndex = 50 + 4 * half_quarter_bot_and_top + 3;
		}
		else
		{
			face[fei].vert[3].vertIndex = 50 + 4 * half_quarter_bot_and_top + 0;
			face[fei].vert[2].vertIndex = 50 + 4 * half_quarter_bot_and_top + 1;
			face[fei].vert[1].vertIndex = 50 + 4 * half_quarter_bot_and_top + 2;
			face[fei].vert[0].vertIndex = 50 + 4 * half_quarter_bot_and_top + 3;
		}
		fei++;
	}
	for (int half_quarter = 0; half_quarter < 2; half_quarter++)
	{
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		if (half_quarter == 0)
		{
			face[fei].vert[0].vertIndex = 50 + 4 * half_quarter + 0;
			face[fei].vert[1].vertIndex = 50 + 4 * half_quarter + 1;
			face[fei].vert[2].vertIndex = 50 + 4 * (half_quarter + 2) + 1;
			face[fei].vert[3].vertIndex = 50 + 4 * (half_quarter + 2) + 0;
		}
		else
		{
			face[fei].vert[3].vertIndex = 50 + 4 * half_quarter + 0;
			face[fei].vert[2].vertIndex = 50 + 4 * half_quarter + 1;
			face[fei].vert[1].vertIndex = 50 + 4 * (half_quarter + 2) + 1;
			face[fei].vert[0].vertIndex = 50 + 4 * (half_quarter + 2) + 0;
		}
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
		if (half_quarter == 0)
		{
			face[fei].vert[0].vertIndex = 50 + 4 * half_quarter + 2;
			face[fei].vert[1].vertIndex = 50 + 4 * half_quarter + 3;
			face[fei].vert[2].vertIndex = 50 + 4 * (half_quarter + 2) + 3;
			face[fei].vert[3].vertIndex = 50 + 4 * (half_quarter + 2) + 2;
		}
		else
		{
			face[fei].vert[3].vertIndex = 50 + 4 * half_quarter + 2;
			face[fei].vert[2].vertIndex = 50 + 4 * half_quarter + 3;
			face[fei].vert[1].vertIndex = 50 + 4 * (half_quarter + 2) + 3;
			face[fei].vert[0].vertIndex = 50 + 4 * (half_quarter + 2) + 2;
		}
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
		if (half_quarter_bot_and_top % 2)
		{
			face[fei].vert[0].vertIndex = 70 + 4 * half_quarter_bot_and_top + 0;
			face[fei].vert[1].vertIndex = 70 + 4 * half_quarter_bot_and_top + 1;
			face[fei].vert[2].vertIndex = 70 + 4 * half_quarter_bot_and_top + 2;
			face[fei].vert[3].vertIndex = 70 + 4 * half_quarter_bot_and_top + 3;
		}
		else
		{
			face[fei].vert[3].vertIndex = 70 + 4 * half_quarter_bot_and_top + 0;
			face[fei].vert[2].vertIndex = 70 + 4 * half_quarter_bot_and_top + 1;
			face[fei].vert[1].vertIndex = 70 + 4 * half_quarter_bot_and_top + 2;
			face[fei].vert[0].vertIndex = 70 + 4 * half_quarter_bot_and_top + 3;
		}
		fei++;
	}
	for (int half_quarter = 0; half_quarter < 2; half_quarter++)
	{
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[3].vertIndex = 70 + 4 * half_quarter + 0;
		face[fei].vert[2].vertIndex = 70 + 4 * half_quarter + 1;
		face[fei].vert[1].vertIndex = 70 + 4 * (half_quarter + 2) + 1;
		face[fei].vert[0].vertIndex = 70 + 4 * (half_quarter + 2) + 0;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[3].vertIndex = 70 + 4 * half_quarter + 1;
		face[fei].vert[2].vertIndex = 70 + 4 * half_quarter + 2;
		face[fei].vert[1].vertIndex = 70 + 4 * (half_quarter + 2) + 2;
		face[fei].vert[0].vertIndex = 70 + 4 * (half_quarter + 2) + 1;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[3].vertIndex = 70 + 4 * half_quarter + 2;
		face[fei].vert[2].vertIndex = 70 + 4 * half_quarter + 3;
		face[fei].vert[1].vertIndex = 70 + 4 * (half_quarter + 2) + 3;
		face[fei].vert[0].vertIndex = 70 + 4 * (half_quarter + 2) + 2;
		fei++;
		face[fei].nVerts = 4;
		face[fei].vert = new VertexID[face[fei].nVerts];
		face[fei].vert[3].vertIndex = 70 + 4 * half_quarter + 3;
		face[fei].vert[2].vertIndex = 70 + 4 * half_quarter + 0;
		face[fei].vert[1].vertIndex = 70 + 4 * (half_quarter + 2) + 0;
		face[fei].vert[0].vertIndex = 70 + 4 * (half_quarter + 2) + 3;
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
}

void Base::Draw()
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


#pragma endregion
// Bar
#pragma region
class Bar : public Mesh
{
public:
	float fHeight;
	float fShortWidth;
	float fLongWidth;
	float fLength;

	Bar(float fHeight, float fShortWidth, float fLongWidth, float fLength) : fHeight(fHeight), fShortWidth(fShortWidth), fLongWidth(fLongWidth), fLength(fLength) {};
	void create();
	void Draw();
};
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
#pragma endregion
// Cube
#pragma region
class Cube : public Mesh
{
public:
	float fSize;
	Cube(float fSize) : fSize(fSize) {};
	void create();
	void Draw();
};
void Cube::create()
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
}

void Cube::Draw()
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
#pragma endregion
// PieceBar
#pragma region
class PieceBar : public Mesh
{
public:
	float fHeight;
	float fMainWidth;
	float fSubWidth;
	float fLength;

	PieceBar(float fHeight, float fMainWidth, float fSubWidth, float fLength) : fHeight(fHeight), fMainWidth(fMainWidth), fSubWidth(fSubWidth), fLength(fLength) {};
	void create();
	void Draw();
};
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

#pragma endregion

enum colorMode
{
	Wired,
	Colored
};

enum cameraMode
{
	__3D,
	__2D
};
/// Global display settings
int screenWidth = 1080;
int screenHeight = 720;

colorMode e_colorMode = Colored;
cameraMode e_cameraMode = __3D;

/// Size of Objects
// MAIN CROSSBASE
float fMainHeight = 1;
float fGrooveHeight = 0.5;
float fLength = 4.5;
// assume: fMainWidth = 2 * fSubWidth + fGrooveWidth
float fMainWidth = 1;
float fSubWidth = 0.3;
float fGrooveWidth = 0.4;
// TIE BAR
float tieBar_length = 4.6;
float tieBar_long_width = 0.4;
float tieBar_short_width = 0.6;
float tieBar_height = 0.4;
// LATCH CYLINDER X / Z / CENTER
float latchCylinder_radius = fGrooveWidth / 2 - 0.1;
float latchCylinder_height = fMainHeight - fGrooveHeight + 0.3;
// SLIDER X / Z
float slider_height = fMainHeight - fGrooveHeight;
float slider_width = fGrooveWidth;
float slider_length = 1; // FLength / 5

float sliderMax_pos = 4;
float m_angle = 45;
float sliderX_pos = 4 * cos(DEG2RAD(m_angle));
float sliderZ_pos = 4 * sin(DEG2RAD(m_angle));

// Local camera papameters
float m_angleX = 0;
float m_angleZ = 0;

/// Global camera settings
float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

/// Mesh of Objects
Base crossbase = Base(fMainHeight, fGrooveHeight, fMainWidth, fSubWidth, fGrooveWidth, fLength);
Cylinder latchCylinderX = Cylinder(20, latchCylinder_height, latchCylinder_radius);
Cylinder latchCylinderZ = Cylinder(20, latchCylinder_height, latchCylinder_radius);
Cylinder latchCylinderCenter = Cylinder(20, latchCylinder_height, latchCylinder_radius);
Bar tiebar = Bar(tieBar_height, tieBar_short_width, tieBar_long_width, tieBar_length);
Cube sliderX = Cube(0.5);
Cube sliderZ = Cube(0.5);

// Mesh of addition objects
// Support Mesh for buidling Tshape
Cube temp1 = Cube(1);
Cube temp2 = Cube(1);
Cylinder temp3 = Cylinder(30, 0.6, 0.8);
Cylinder temp4 = Cylinder(30, 0.6, 0.8);
Cylinder temp5 = Cylinder(30, 0.6, 0.8);
Cylinder temp6 = Cylinder(30, 0.6, 0.8);
Cylinder temp7 = Cylinder(30, 0.6, 0.8);
// Support Mesh for building 5-bar
PieceBar sup_5bar_1 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_5bar_2 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_5bar_3 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_5bar_4 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_5bar_5 = PieceBar(1, 1, 0.3, 4.5);
// Support Mesh for building 5-bar
PieceBar sup_6bar_1 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_6bar_2 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_6bar_3 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_6bar_4 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_6bar_5 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_6bar_6 = PieceBar(1, 1, 0.3, 4.5);
// Support Mesh for building 8-bar
PieceBar sup_8bar_1 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_8bar_2 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_8bar_3 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_8bar_4 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_8bar_5 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_8bar_6 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_8bar_7 = PieceBar(1, 1, 0.3, 4.5);
PieceBar sup_8bar_8 = PieceBar(1, 1, 0.3, 4.5);

// Opengl coordinate convention
// x-axis extends to the right
// y-axis extends upwards
// z-axis extends toward the viewer, coming out of the screen.
void drawAxis()
{
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0); // red
		glVertex3f(0, 0, 0);
		glVertex3f(4, 0, 0);
	}
	{
		glColor3f(0, 1, 0); // green
		glVertex3f(0, 0, 0);
		glVertex3f(0, 4, 0);
	}
	{
		glColor3f(0, 0, 1); // blue
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 4);
	}
	glEnd();
}

void setMaterial(float ar, float ag, float ab,
	float dr, float dg, float db,
	float sr, float sg, float sb)
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shiness = 100.8;

	ambient[0] = ar;
	ambient[1] = ag;
	ambient[2] = ab;
	ambient[3] = 1;
	diffuse[0] = dr;
	diffuse[1] = dg;
	diffuse[2] = db;
	diffuse[3] = 1;
	specular[0] = sr;
	specular[1] = sg;
	specular[2] = sb;
	specular[3] = 1;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}
void setLight()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	const GLfloat leftLightAmbColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	const GLfloat leftLightSpecColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat leftLightDiffColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	const GLfloat leftLightPos[] = { -5.0, -5.0, -5.0, 0.0 };

	// set up left light
	glLightfv(GL_LIGHT1, GL_POSITION, leftLightPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, leftLightAmbColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, leftLightDiffColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, leftLightSpecColor);
	glEnable(GL_LIGHT1);
}

void drawPattern(float x, float y, float z, float square_size)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor4f(1.0, 0.25, 0.25, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x + square_size, y, z);
	glVertex3f(x + square_size, y, z + square_size);
	glVertex3f(x, y, z + square_size);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0.0, 1.0, 1.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z + square_size);
	glVertex3f(x + square_size / 2, y, z + square_size * 3 / 2);
	glVertex3f(x + square_size / 2, y, z + square_size * 2);
	glVertex3f(x, y, z + square_size * 3 / 2);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + square_size, y, z + square_size);
	glVertex3f(x + square_size, y, z + square_size * 3 / 2);
	glVertex3f(x + square_size / 2, y, z + square_size * 2);
	glVertex3f(x + square_size / 2, y, z + square_size * 3 / 2);
	glEnd();
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor4f(0.0, 1.0, 1.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + square_size, y, z + square_size);
	glVertex3f(x + square_size * 3 / 2, y, z + square_size / 2);
	glVertex3f(x + square_size * 2, y, z + square_size / 2);
	glVertex3f(x + square_size * 3 / 2, y, z + square_size);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + square_size, y, z);
	glVertex3f(x + square_size * 3 / 2, y, z);
	glVertex3f(x + square_size * 2, y, z + square_size / 2);
	glVertex3f(x + square_size * 3 / 2, y, z + square_size / 2);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0.0, 1.0, 1.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + square_size, y, z);
	glVertex3f(x + square_size, y, z - square_size / 2);
	glVertex3f(x + square_size / 2, y, z - square_size);
	glVertex3f(x + square_size / 2, y, z - square_size / 2);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x + square_size / 2, y, z - square_size / 2);
	glVertex3f(x + square_size / 2, y, z - square_size);
	glVertex3f(x, y, z - square_size / 2);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0.0, 1.0, 1.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z);
	glVertex3f(x - square_size / 2, y, z + square_size / 2);
	glVertex3f(x - square_size, y, z + square_size / 2);
	glVertex3f(x - square_size / 2, y, z);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, z + square_size);
	glVertex3f(x - square_size / 2, y, z + square_size);
	glVertex3f(x - square_size, y, z + square_size / 2);
	glVertex3f(x - square_size / 2, y, z + square_size / 2);
	glEnd();

	glPopMatrix();
}

void drawFloor()
{
	float y = 0;
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	// Explain
	// square_size = 2
	// increment = 3 = 1.5 * square_size b/c of the way drawing each square
	// -90 and 90 is choosen by incident
	// <-90, 90> * 3 aim to get integer value (tragetting modulo 2)
	for (int x = -90 * 3; x < 90 * 3; x += 3)
	{
		for (int z = -90 * 3; z < 90 * 3; z += 3)
		{
			if ((x + z) % 2 == 0)
				drawPattern(x, -10, z, 2);
		}
	}
	glEnable(GL_LIGHTING);
}

void drawMainbar()
{
	glPushMatrix();
	if (e_colorMode == Colored)
	{
		setMaterial(1, 0, 0,
			1.0, 0.0, 0.0,
			1.0, 1.0, 1.0);
		crossbase.Draw();
	}
	else
	{
		crossbase.DrawWireframe();
	}
	glPopMatrix();
}

void drawTiebar()
{
	glPushMatrix();
	glTranslatef(0, fMainHeight + tieBar_height, 0);
	glTranslatef(sliderX_pos / 2, 0, sliderZ_pos / 2);
	glRotatef(m_angle, 0, 1, 0);
	glRotatef(180, 1, 0, 0);

	if (e_colorMode == Colored)
	{
		setMaterial(0, 1, 0,
			0.0, 0.0, 0.0,
			1.0, 1.0, 1.0);
		tiebar.Draw();
	}
	else
	{
		tiebar.DrawWireframe();
	}
	glPopMatrix();
}
void draw_3_latch()
{
	glPushMatrix();
	glTranslatef(0, latchCylinder_height / 2 + 0.2, 0);
	glTranslatef(sliderX_pos, fGrooveHeight, 0);

	if (e_colorMode == Colored)
	{
		setMaterial(1, 1, 0,
			1.0, 1.0, 0.0,
			1.0, 1.0, 1.0);
		latchCylinderX.Draw();
	}
	else
	{
		latchCylinderX.DrawWireframe();
	}

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, latchCylinder_height / 2 + 0.2, 0);
	glTranslatef(0, fGrooveHeight, sliderZ_pos);
	if (e_colorMode == Colored)
	{
		latchCylinderZ.Draw();
	}
	else
	{
		latchCylinderZ.DrawWireframe();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, latchCylinder_height / 2 + fMainHeight + 0.01, 0);
	glTranslatef(sliderX_pos / 2, 0, sliderZ_pos / 2);
	if (e_colorMode == Colored)
	{
		latchCylinderCenter.Draw();
	}
	else
	{
		latchCylinderCenter.DrawWireframe();
	}
	glPopMatrix();
}

void draw_2_slider()
{
	glPushMatrix();
	glScalef(slider_length, slider_height, slider_width);
	glTranslatef(0, fMainHeight, 0);
	glTranslatef(sliderX_pos, fGrooveHeight, 0);
	if (e_colorMode == Colored)
	{
		setMaterial(0, 0, 1,
			0.0, 0.0, 0.0,
			1.0, 1.0, 1.0);
		sliderX.Draw();
	}
	else
	{
		sliderX.DrawWireframe();
	}
	glPopMatrix();

	glPushMatrix();
	glScalef(slider_width, slider_height, slider_length);
	glTranslatef(0, fMainHeight, 0);
	glTranslatef(0, fGrooveHeight, sliderZ_pos);
	if (e_colorMode == Colored)
	{
		sliderZ.Draw();
	}
	else
	{
		sliderZ.DrawWireframe();
	}
	glPopMatrix();
}

void drawMainMechainism()
{
	/// local x-axis map to axis-X in real world
	/// local y-axis map to axis-Z in real world
	/// The height is always the axis-Y
	/// CHANGE MODE BETWEEN DRAW COLORED OR WIREFRAME IS ALSO ALLOWED.
	//// Local ROTATE ALLOWED
	glPushMatrix();
	glRotatef(m_angleX, 1, 0, 0);
	glRotatef(m_angleZ, 0, 0, 1);
	// Display Main CrossBar
	drawMainbar();
	// Display the Tie bar (connecting object)
	drawTiebar();
	// Display 3 latch cylinder
	draw_3_latch();
	// Display 2 slider
	draw_2_slider();

	glPopMatrix();
}

void drawTshape()
{
	glPushMatrix();
	glTranslatef(-20.0, 10, -20);
	glRotatef(90, 1, 0, 0);

	// X-bar
	glPushMatrix();
	glScalef(0.8, 0.3, 4);
	if (e_colorMode == Colored)
	{
		setMaterial(1, 0, 0,
			0.0, 0.0, 0.0,
			1.0, 1.0, 1.0);
		temp1.Draw();
	}
	else
	{
		temp1.DrawWireframe();
	}
	glPopMatrix();
	// y-bar
	glPushMatrix();
	glScalef(4, 0.3, 0.8);
	glTranslatef(0, 0, -6);
	if (e_colorMode == Colored)
	{
		temp2.Draw();
	}
	else
	{
		temp2.DrawWireframe();
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 4);
	if (e_colorMode == Colored)
	{
		temp3.Draw();
	}
	else
	{
		temp3.DrawWireframe();
	}
	glPopMatrix();
	// Right half cylinder
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(4 + 0.8, 0, 4);
	if (e_colorMode == Colored)
	{
		temp4.Draw();
	}
	else
	{
		temp4.DrawWireframe();
	}
	glPopMatrix();
	// Left half cylinder
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(-4 - 0.8, 0, 4);
	if (e_colorMode == Colored)
	{

		temp5.Draw();
	}
	else
	{
		temp5.DrawWireframe();
	}
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(2 + 0.6 * 2, 0, -0.8 * 2);
	if (e_colorMode == Colored)
	{
		temp6.Draw();
	}
	else
	{
		temp6.DrawWireframe();
	}
	glPopMatrix();
	glPushMatrix();
	glRotatef(-180, 0, 1, 0);
	glTranslatef(-0.8 * 2, 0, 2 + 0.6 * 2);
	if (e_colorMode == Colored)
	{
		temp7.Draw();
	}
	else
	{
		temp7.DrawWireframe();
	}
	glPopMatrix();
	glPopMatrix();
}

void addAdistance(float fMainWidth, float angle)
{
	glTranslatef(0, 0, fMainWidth / (2 * tan(DEG2RAD(angle / 2))));
}

void drawIsoscelesPolygon(int numVertices, float size, float fMainHeight)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < numVertices; ++i)
	{
		float angle = 2.0f * M_PI * i / numVertices; // Calculate angle for each vertex
		float x = size * cos(angle);				 // Calculate x coordinate
		float z = size * sin(angle);				 // Calculate z coordinate
		glVertex3f(x, 0, z);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < numVertices; ++i)
	{
		float angle = 2.0f * M_PI * i / numVertices; // Calculate angle for each vertex
		float x = size * cos(angle);				 // Calculate x coordinate
		float z = size * sin(angle);				 // Calculate z coordinate
		glVertex3f(x, fMainHeight / 2, z);
	}
	glEnd();
}

float calculateRadius(float fMainWidth, float angle)
{
	return fMainWidth / (2 * sin(DEG2RAD(angle / 2)));
}

void draw_5bar()
{
	glPushMatrix();
	glTranslatef(20.0, 10, 20);
	glRotatef(-90, 1, 0, 0);

	{
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		drawIsoscelesPolygon(5, calculateRadius(1, 72), 1);
		glPopMatrix();
	}

	{
		glPushMatrix();
		addAdistance(1, 72);

		if (e_colorMode == Colored)
		{
			setMaterial(1, 0, 0,
				0.0, 0.0, 0.0,
				1.0, 1.0, 1.0);
			sup_5bar_1.Draw();
		}
		else
		{
			sup_5bar_1.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();

		glRotatef(72, 0, 1, 0);
		addAdistance(1, 72);

		if (e_colorMode == Colored)
		{
			sup_5bar_2.Draw();
		}
		else
		{
			sup_5bar_2.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();

		glRotatef(72 * 2, 0, 1, 0);
		addAdistance(1, 72);

		if (e_colorMode == Colored)
		{
			sup_5bar_3.Draw();
		}
		else
		{
			sup_5bar_3.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();

		glRotatef(72 * 3, 0, 1, 0);
		addAdistance(1, 72);

		if (e_colorMode == Colored)
		{
			sup_5bar_4.Draw();
		}
		else
		{
			sup_5bar_4.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();

		glRotatef(72 * 4, 0, 1, 0);
		addAdistance(1, 72);

		if (e_colorMode == Colored)
		{
			sup_5bar_5.Draw();
		}
		else
		{
			sup_5bar_5.DrawWireframe();
		}
		glPopMatrix();
	}

	glPopMatrix();
}

void draw_6bar()
{
	glPushMatrix();

	glTranslatef(-20.0, 10, 20);
	glRotatef(-90, 1, 0, 0);

	{
		glPushMatrix();
		drawIsoscelesPolygon(6, calculateRadius(1, 60), 1);
		glPopMatrix();
	}
	{
		glPushMatrix();
		addAdistance(1, 60);

		if (e_colorMode == Colored)
		{
			setMaterial(1, 0, 0,
				0.0, 0.0, 0.0,
				1.0, 1.0, 1.0);
			sup_6bar_1.Draw();
		}
		else
		{
			sup_6bar_1.DrawWireframe();
		}
		glPopMatrix();
	}

	{
		glPushMatrix();
		glRotatef(60, 0, 1, 0);
		addAdistance(1, 60);

		if (e_colorMode == Colored)
		{
			sup_6bar_2.Draw();
		}
		else
		{
			sup_6bar_2.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();
		glRotatef(60 * 2, 0, 1, 0);
		addAdistance(1, 60);

		if (e_colorMode == Colored)
		{
			sup_6bar_3.Draw();
		}
		else
		{
			sup_6bar_3.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();
		glRotatef(60 * 3, 0, 1, 0);
		addAdistance(1, 60);

		if (e_colorMode == Colored)
		{
			sup_6bar_4.Draw();
		}
		else
		{
			sup_6bar_4.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();
		glRotatef(60 * 4, 0, 1, 0);
		addAdistance(1, 60);

		if (e_colorMode == Colored)
		{
			sup_6bar_5.Draw();
		}
		else
		{
			sup_6bar_5.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();
		glRotatef(60 * 5, 0, 1, 0);
		addAdistance(1, 60);

		if (e_colorMode == Colored)
		{
			sup_6bar_6.Draw();
		}
		else
		{
			sup_6bar_6.DrawWireframe();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void draw_8bar()
{
	glPushMatrix();

	glTranslatef(20.0, 10, -20);
	glRotatef(-90, 1, 0, 0);

	{
		glPushMatrix();
		glRotatef(45 / 2, 0, 1, 0);
		drawIsoscelesPolygon(8, calculateRadius(1, 45), 1);
		glPopMatrix();
	}
	{
		glPushMatrix();
		addAdistance(1, 45);
		if (e_colorMode == Colored)
		{
			setMaterial(1, 0, 0,
				0.0, 0.0, 0.0,
				1.0, 1.0, 1.0);
			sup_8bar_1.Draw();
		}
		else
		{
			sup_8bar_1.DrawWireframe();
		}
		glPopMatrix();
	}

	{
		glPushMatrix();
		glRotatef(45, 0, 1, 0);
		addAdistance(1, 45);

		if (e_colorMode == Colored)
		{
			sup_8bar_2.Draw();
		}
		else
		{
			sup_8bar_2.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();
		glRotatef(45 * 2, 0, 1, 0);
		addAdistance(1, 45);

		if (e_colorMode == Colored)
		{
			sup_8bar_3.Draw();
		}
		else
		{
			sup_8bar_3.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();
		glRotatef(45 * 3, 0, 1, 0);
		addAdistance(1, 45);

		if (e_colorMode == Colored)
		{
			sup_8bar_4.Draw();
		}
		else
		{
			sup_8bar_4.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();
		glRotatef(45 * 4, 0, 1, 0);
		addAdistance(1, 45);

		if (e_colorMode == Colored)
		{
			sup_8bar_5.Draw();
		}
		else
		{
			sup_8bar_5.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();
		glRotatef(45 * 5, 0, 1, 0);
		addAdistance(1, 45);

		if (e_colorMode == Colored)
		{
			sup_8bar_6.Draw();
		}
		else
		{
			sup_8bar_6.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();
		glRotatef(45 * 6, 0, 1, 0);
		addAdistance(1, 45);

		if (e_colorMode == Colored)
		{
			sup_8bar_7.Draw();
		}
		else
		{
			sup_8bar_7.DrawWireframe();
		}
		glPopMatrix();
	}
	{
		glPushMatrix();
		glRotatef(45 * 7, 0, 1, 0);
		addAdistance(1, 45);

		if (e_colorMode == Colored)
		{
			sup_8bar_8.Draw();
		}
		else
		{
			sup_8bar_8.DrawWireframe();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void myDisplay()
{
	////////////////////////////////////////////////////////////////////////
	//////  INIT DYNMAMIC OBJECTS (that oviously changes wihtin runtime)
	////////////////////////////////////////////////////////////////////////
	//////  [!!!] STATIC Objects will be initialized in MAIN function
	////////////////////////////////////////////////////////////////////////
	// Turn on 2 LIGHT SOURCE
	/*
		Issues:
			- W press make changes in colors of mesh objects
			- set material not ready maybe the issue.
			- black and red are mostly displayed.
	*/
	if (e_colorMode == Colored)
		setLight();
	else
		glDisable(GL_LIGHT0);

	// Allowing the matrix operation applied onto current modelview matrix stack
	// Comparing with GL_PROJECTION which is used to specify the projection transformation determining how 3d objects are
	// projected onto 2D viewport
	glMatrixMode(GL_MODELVIEW);
	// Load identity means replace current matrix with the identity matrix recognizing as a special matrix where all
	// diagonal elements are 1 and others are 0
	glLoadIdentity();
	if (e_cameraMode == __2D)
		gluLookAt(0, 10, 0, 0, 0, 0, -1, 0, 0);
	else
		gluLookAt(camera_X, camera_Y, camera_Z, 0, 0, 0, 0, 1, 0);
	// Clear buffers to prepare for rendering new frame
	// just only glEnable(GL_DEPTH_TEST) have been enabled before so that the following for depth need being called
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// gl view port which set port of view in the current screen
	/// ALLOW ROTATE AROUND ITS STRUCTURE AXIS

	// Floor DISPLAY
	drawFloor();
	// Main model DISPLAY
	drawMainMechainism();
	// ADDITION model DISPLAY
	// Tshape
	drawTshape();
	// 5bar;
	draw_5bar();
	// 6bar
	draw_6bar();
	// 8bar
	draw_8bar();

	// 	CURRENTLY NOT USE (B/C I BELIEVE VIEWPORT NOT WORK WITH gluPerspective)
	// 	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	// glViewport(0, 0, screenWidth, screenHeight);
	// {
	// 	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 	///////////////////////////////////////////////// END OF VIEW PORT /////////////////////////////////////////////////
	// 	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// }
	glutPostRedisplay();
	// Perform rendering operations
	glFlush();
	glutSwapBuffers();
}

void changeCameraPos()
{
	camera_X = sin(DEG2RAD(camera_angle)) * camera_dis;
	camera_Y = camera_height;
	camera_Z = cos(DEG2RAD(camera_angle)) * camera_dis;
	myDisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // ESC key
	{
		exit(0);
		break;
	}
	case 'w':
	case 'W':
	{
		e_colorMode = (e_colorMode == Wired) ? Colored : Wired;
		break;
	}
	case '1':
	{
		float dx = 2;
		m_angleX += dx;
		if (m_angleX >= 360)
			m_angleX = 0;
		break;
	}
	case '2':
	{
		float dx = 2;
		m_angleX -= dx;
		if (m_angleX <= -360)
			m_angleX = 0;
		break;
	}
	case '3':
	{
		float dz = 2;
		m_angleZ += dz;
		if (m_angleZ >= 360)
			m_angleZ = 0;
		break;
	}
	case '4':
	{
		float dz = 2;
		m_angleZ -= dz;
		if (m_angleZ <= -360)
			m_angleZ = 0;
		break;
	}
	case '5':
	{
		float dx = 2;
		m_angle += dx;
		if (m_angle >= 360)
			m_angle = 0;
		sliderX_pos = 4 * cos(DEG2RAD(m_angle));
		sliderZ_pos = 4 * sin(DEG2RAD(m_angle));
		break;
	}
	case '6':
	{
		float dx = 2;
		m_angle -= dx;
		if (m_angle <= -360)
			m_angle = 0;
		sliderX_pos = 4 * cos(DEG2RAD(m_angle));
		sliderZ_pos = 4 * sin(DEG2RAD(m_angle));
		break;
	}
	case '+':
	{
		camera_dis += 0.9f;
		changeCameraPos();
		break;
	}
	case '-':
	{
		camera_dis -= 0.9f;
		changeCameraPos();
		break;
	}
	case 'v':
	case 'V':
	{
		e_cameraMode = (e_cameraMode == __3D) ? __2D : __3D;
		break;
	}
	default:
		break;
	}

	glutPostRedisplay();
	// printf("[LOG:::BUTTON] button[%c] is pressed.\n", key);
}

void mySpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.9f;
		changeCameraPos();
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.9f;
		changeCameraPos();
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 0.9f;
		changeCameraPos();
		break;
	case GLUT_KEY_LEFT:
		camera_angle -= 0.9f;
		changeCameraPos();
		break;
	default:
		// Handle other keys if needed
		break;
	}
	// printf("[LOG:::BUTTON] button[%c] is pressed.\n", key);
	glutPostRedisplay();
	// printf("CameraX = %f, CameraY = %f, CameraZ = %f\n", camera_X, camera_Y, camera_Z);
}

void myInit()
{
	float fHalfSize = 12;
	// rgba format
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Set orientation of front-facing polygon: [C]ounter[C]lock[W]ise
	// Another option is GL_CW
	// front-facing means the front ground of a picture
	glFrontFace(GL_CCW);
	// Depth test allow depth value of pixels (represent as z-cooordinate) is compared to the depth value in
	// depth buffer. If the new pixel is closer to camera (has a similar depth value) than the existing value
	// in the depth buffer, the pixel is drawn. Otherwise, it should be ignored.
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 1.0f, 1000.0f);

	camera_angle = 45;
	camera_height = 8;
	camera_dis = 4;
	camera_X = sin(DEG2RAD(camera_angle)) * camera_dis;
	camera_Y = camera_height;
	camera_Z = cos(DEG2RAD(camera_angle)) * camera_dis;
}

void showInstructions()
{
	cout << "1, 2       : Xoay hinh chu thap xung quanh truc Y cuc bo\n";
	cout << "3, 4       : Xoay hinh chu thap xung quanh truc X cuc bo\n";
	cout << "5, 6       : Dich chuyen thanh truot\n";
	cout << "W, w       : Chuyen doi qua lai giua che do khung day va to mau\n";
	cout << "V, v  	    : Chuyen doi qua lai giua hai che do nhin\n";
	cout << "+          : Tang khoang cach camera\n";
	cout << "-     	    : Giam khoang cach camera\n";
	cout << "up arrow   : Tang chieu cao camera\n";
	cout << "down arrow : Giam chieu cao camera\n";
	cout << "<-         : Quay camera theo chieu kim dong ho\n";
	cout << "->         : Quay camera nguoc chieu kim dong ho\n";
	cout << "Esc		: Thoat chuong trinh\n";
}

void createMainMechainism()
{
	crossbase.create();
	crossbase.CalculateFacesNorm();
	tiebar.create();
	tiebar.CalculateFacesNorm();
	latchCylinderX.create();
	latchCylinderX.CalculateFacesNorm();
	latchCylinderZ.create();
	latchCylinderZ.CalculateFacesNorm();
	latchCylinderCenter.create();
	latchCylinderCenter.CalculateFacesNorm();
	sliderX.create();
	sliderX.CalculateFacesNorm();
	sliderZ.create();
	sliderZ.CalculateFacesNorm();
}

void createTshape()
{
	temp1.create();
	temp1.CalculateFacesNorm();

	temp2.create();
	temp2.CalculateFacesNorm();

	temp3.create_alpha(180);
	temp3.CalculateFacesNorm();

	temp4.create_alpha(180);
	temp4.CalculateFacesNorm();

	temp5.create_alpha(180);
	temp5.CalculateFacesNorm();

	temp6.create_compensation(90);
	temp6.CalculateFacesNorm();

	temp7.create_compensation(90);
	temp7.CalculateFacesNorm();
}

void create_5bar()
{
	sup_5bar_1.create();
	sup_5bar_1.CalculateFacesNorm();
	sup_5bar_2.create();
	sup_5bar_2.CalculateFacesNorm();
	sup_5bar_3.create();
	sup_5bar_3.CalculateFacesNorm();
	sup_5bar_4.create();
	sup_5bar_4.CalculateFacesNorm();
	sup_5bar_5.create();
	sup_5bar_5.CalculateFacesNorm();
}

void create_6bar()
{
	sup_6bar_1.create();
	sup_6bar_1.CalculateFacesNorm();
	sup_6bar_2.create();
	sup_6bar_2.CalculateFacesNorm();
	sup_6bar_3.create();
	sup_6bar_3.CalculateFacesNorm();
	sup_6bar_4.create();
	sup_6bar_4.CalculateFacesNorm();
	sup_6bar_5.create();
	sup_6bar_5.CalculateFacesNorm();
	sup_6bar_6.create();
	sup_6bar_6.CalculateFacesNorm();
}

void create_8bar()
{
	sup_8bar_1.create();
	sup_8bar_1.CalculateFacesNorm();
	sup_8bar_2.create();
	sup_8bar_2.CalculateFacesNorm();
	sup_8bar_3.create();
	sup_8bar_3.CalculateFacesNorm();
	sup_8bar_4.create();
	sup_8bar_4.CalculateFacesNorm();
	sup_8bar_5.create();
	sup_8bar_5.CalculateFacesNorm();
	sup_8bar_6.create();
	sup_8bar_6.CalculateFacesNorm();
	sup_8bar_7.create();
	sup_8bar_7.CalculateFacesNorm();
	sup_8bar_8.create();
	sup_8bar_8.CalculateFacesNorm();
}

int main(int argc, char* argv[])
{
	// Display instruction to control the application
	showInstructions();
	// Opengl Main display program
	glutInit(&argc, (char**)argv);							  // initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set the display mode
	glutInitWindowSize(screenWidth, screenHeight);			  // set window size
	glutInitWindowPosition(100, 100);						  // set window position on screen
	glutCreateWindow("Computer Graphic Assignment - Nguyen Le Gia Hinh - 2011213");		  // open the screen window

	////////////////////////////////////////////////////////////////////////
	//////  CREATE OBJECTS
	////////////////////////////////////////////////////////////////////////
	createMainMechainism();
	createTshape();
	create_5bar();
	create_6bar();
	create_8bar();
	// Init opengl environment
	myInit();
	// Function to display main presentation
	glutDisplayFunc(myDisplay);
	// Function in idle mode
	// Setup the keyboard function triggering callback (special keyboard included)
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutMainLoop();

	return 0;
}
