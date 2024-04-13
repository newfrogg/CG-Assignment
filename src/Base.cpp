#include "Base.h"

void Base::create() {
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
}

void Base::Draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;

			glColor3f(124.0f / 255, 124.0f / 255, 122.0f / 255);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}