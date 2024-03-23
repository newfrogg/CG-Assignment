#include <math.h>
#include <iostream>
#include <vector>
#include "supportClass.h"
#include "Mesh.h"
#include "matrix.h"

using namespace std;

int screenWidth = 1080;
int screenHeight = 480;

Mesh tetrahedron;
Mesh cube;
Mesh shape1;
Mesh temp;
Mesh shape2;
Mesh cylinder;

int nChoice;
float eyeX = 4.5;
float eyeY = 4;
float eyeZ = 2;

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

void myDisplay()
{
	// Allowing the matrix operation applied onto current modelview matrix stack
	// Comparing with GL_PROJECTION which is used to specify the projection transformation determining how 3d objects are
	// projected onto 2D viewport
	glMatrixMode(GL_MODELVIEW);
	// Load identity means replace current matrix with the identity matrix recognizing as a special matrix where all
	// diagonal elements are 1 and others are 0
	glLoadIdentity();
	// (Eye, center, up)
	gluLookAt(
		eyeX,
		eyeY,
		eyeZ,
		0, 0, 0, 0, 1, 0);
	// Clear buffers to prepare for rendering new frame
	// just only glEnable(GL_DEPTH_TEST) have been enabled before so that the following for depth need being called
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// gl view port which set port of view in the current screen
	glViewport(0, 0, screenWidth / 2, screenHeight);
	{
		drawAxis();
		glColor3f(0, 0, 0);
		if (nChoice == 1)
			tetrahedron.DrawWireframe();
		else if (nChoice == 0)
			cylinder.DrawWireframe();
		else if (nChoice == 2)
			cube.DrawWireframe();
		else if (nChoice == 3)
			shape1.DrawWireframe();
		else if (nChoice == 4)
			temp.DrawWireframe();
		else if (nChoice == 5)
			shape2.DrawWireframe();
	}

	glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);
	{
		drawAxis();
		if (nChoice == 1)
			tetrahedron.DrawColor();
		else if (nChoice == 0)
			cylinder.DrawColor();
		else if (nChoice == 2)
			cube.DrawColor();
		else if (nChoice == 3)
			shape1.DrawColor();
		else if (nChoice == 4)
			temp.DrawColor();
		else if (nChoice == 5)
			shape2.DrawColor();
	}
	// Perform rendering operations
	glFlush();
	glutSwapBuffers();
}

void keyboardCallback(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		printf("[LOG::RESULT] Program exit successfully.\n");
		exit(0);
	}

	switch (key)
	{
	case '+':
		eyeZ += 0.1f;
		break;
	case '-':
		eyeZ -= 0.1f;
		break;
	case 'a':
		eyeX -= 0.1f;
		break;
	case 'd':
		eyeX += 0.1f;
		break;
	case 'w':
		eyeY += 0.1f;
		break;
	case 's':
		eyeY -= 0.1f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
	printf("[LOG:::BUTTON] button[%c] is pressed.\n", key);
	printf("[LOG:::COORDINATE] eyeX = %f, eyeY = %f, eyeZ = %f\n", eyeX, eyeY, eyeZ);
}

void myInit()
{
	float fHalfSize = 4;
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
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int main(int argc, char *argv[])
{
	nChoice = 4;

	glutInit(&argc, (char **)argv);							  // initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set the display mode
	glutInitWindowSize(screenWidth, screenHeight);			  // set window size
	glutInitWindowPosition(100, 100);						  // set window position on screen
	glutCreateWindow("Lab 2");								  // open the screen window

	tetrahedron.CreateTetrahedron();
	cube.CreateCube(1);
	shape1.CreateTrapezium(1, 1 + 0.2, 2, 4);
	// temp.CreatCrossBase(0, 1, 0.5, 1, 0.3, 0.4, 4);
	temp.CreatCrossBasev2(1, 0.5, 1, 0.3, 0.4, 4);
	// shape2.CreateHandle(1.5, 3, 0.3, 0.8, 0.8, 0.4, 0.4, 0.4);
	// cylinder.CreateCylinder(4, 3, 0.5);
	// Init opengl environment
	myInit();
	// Setup the keyboard function triggering callback
	glutKeyboardFunc(keyboardCallback);
	// Function to display main presentation
	glutDisplayFunc(myDisplay);

	glutMainLoop();

	return 0;
}
