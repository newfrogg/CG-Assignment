#include <math.h>
#include <iostream>
#include <vector>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

enum colorMode
{
	Wired,
	Colored
};

enum movementMode
{
	clockWise,
	counter_clockWise
};

enum cameraMode
{
	__3D,
	__2D
};

/// Global display settings
int screenWidth = 1080;
int screenHeight = 720;

movementMode e_movementModeX = clockWise;
movementMode e_movementModeY = clockWise;
colorMode e_colorMode = Wired;
cameraMode e_cameraMode = __3D;

/// Mesh of Objects
Mesh crossBase;
Mesh latchCylinderX;
Mesh latchCylinderZ;
Mesh latchCylinderCenter;
Mesh tieBar;
Mesh sliderX;
Mesh sliderZ;

/// Size of Objects
// MAIN CROSSBASE
float fMainHeight = 1;
float fGrooveHeight = 0.5;
float fLength = 5;
// assume: fMainWidth = 2 * fSubWidth + fGrooveWidth
float fMainWidth = 1;
float fSubWidth = 0.3;
float fGrooveWidth = 0.4;
// SLIDER X / Z
float slider_height = fMainHeight - fGrooveHeight;
float slider_width = fGrooveWidth;
float slider_length = 1; // FLength / 5
// TIE BAR
float tieBar_length = 4;
float tieBar_long_width = 0.4;
float tieBar_short_width = 0.8;
float tieBar_height = 0.3;
// LATCH CYLINDER X / Z / CENTER
float latchCylinder_radius = fGrooveWidth / 2;
float latchCylinder_height = fMainHeight - fGrooveHeight + 0.2;

float sliderMax_pos = 4;
float m_angle = 0;
float sliderX_pos = 4 * cos(m_angle * M_PI / 180);
float sliderZ_pos = 4 * sin(m_angle * M_PI / 180);

/// Global camera settings
float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

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
	////////////////////////////////////////////////////////////////////////
	//////  INIT DYNMAMIC OBJECTS (that oviously changes wihtin runtime)
	////////////////////////////////////////////////////////////////////////
	//////  [!!!] STATIC Objects will be initialized in MAIN function
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	// Allowing the matrix operation applied onto current modelview matrix stack
	// Comparing with GL_PROJECTION which is used to specify the projection transformation determining how 3d objects are
	// projected onto 2D viewport
	glMatrixMode(GL_MODELVIEW);
	// Load identity means replace current matrix with the identity matrix recognizing as a special matrix where all
	// diagonal elements are 1 and others are 0
	glLoadIdentity();
	// (Eye, center, up)
	gluLookAt(
		4.5, 4, 2,
		0, 0, 0,
		0, 1, 0);
	// Clear buffers to prepare for rendering new frame
	// just only glEnable(GL_DEPTH_TEST) have been enabled before so that the following for depth need being called
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// gl view port which set port of view in the current screen
	glViewport(0, 0, screenWidth, screenHeight);
	{
		drawAxis();
		glPushMatrix();
		if (e_colorMode == Wired)
		{
			glColor3f(0, 0, 1);
			crossBase.DrawWireframe();
			glPushMatrix();
			glTranslatef(0, fMainHeight + tieBar_height, 0);
			glRotatef(180, 1, 0, 0);
			glRotatef(90, 0, 1, 0);
			// tieBar.DrawWireframe();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0, latchCylinder_height / 2, 0);
			glTranslatef(sliderX_pos, fGrooveHeight, 0);
			latchCylinderX.DrawWireframe();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0, latchCylinder_height / 2, 0);
			glTranslatef(0, fGrooveHeight, sliderZ_pos);
			latchCylinderZ.DrawWireframe();
			glPopMatrix();
		}
		else
		{
			glColor3f(0, 0, 1);
			crossBase.DrawColor();

			glPushMatrix();
			glTranslatef(tieBar_length, fMainHeight + tieBar_height, 0);
			glRotatef(180, 1, 0, 0);
			glRotatef(m_angle, 0, 1, 0);
			tieBar.DrawColor();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, latchCylinder_height / 2, 0);
			glTranslatef(sliderX_pos, fGrooveHeight, 0);
			latchCylinderX.DrawColor();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, latchCylinder_height / 2, 0);
			glTranslatef(0, fGrooveHeight, sliderZ_pos);
			latchCylinderZ.DrawColor();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0, latchCylinder_height / 2 + fMainHeight, 0);
			glTranslatef(sliderX_pos / 2, 0, sliderZ_pos / 2);
			latchCylinderCenter.DrawColor();
			glPopMatrix();
		}
		glPopMatrix();
	}

	// Perform rendering operations
	glFlush();
	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // ESC key
		exit(0);
		break;
	case 'w':
	case 'W':
		e_colorMode = (e_colorMode == Wired) ? Colored : Wired;
		break;
	case '1':
	case '2':
		e_movementModeY = (key == '1') ? counter_clockWise : clockWise;
		break;
	case '3':
	case '4':
		e_movementModeX = (key == '3') ? counter_clockWise : clockWise;
		break;
	case '5':
	{
		float dx = 2;
		m_angle += dx;
		if (m_angle >= 360)
			m_angle = 0;
		sliderX_pos = 4 * cos(m_angle * M_PI / 180);
		sliderZ_pos = 4 * sin(m_angle * M_PI / 180);
		break;
	}
	case '6':
	{
		float dx = 2;
		m_angle -= dx;
		if (m_angle <= -360)
			m_angle = 0;
		sliderX_pos = 4 * cos(m_angle * M_PI / 180);
		sliderZ_pos = 4 * sin(m_angle * M_PI / 180);
		break;
	}
	case '+':
		camera_dis += 0.1f;
		break;
	case '-':
		camera_dis -= 0.1f;
		break;
	case 'v':
	case 'V':
		e_cameraMode = (e_cameraMode == __3D) ? __2D : __3D;
		break;
	default:
		break;
	}

	glutPostRedisplay();
	printf("[LOG:::BUTTON] button[%c] is pressed.\n", key);
}

void mySpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		camera_height += 0.1f;
	if (key == GLUT_KEY_DOWN)
		camera_height -= 0.1f;
	if (key == GLUT_KEY_RIGHT)
		camera_angle += 0.1f;
	if (key == GLUT_KEY_LEFT)
		camera_angle -= 0.1f;
	glutPostRedisplay();
}
void myIdle()
{
	myDisplay();
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
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, (char **)argv);							  // initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set the display mode
	glutInitWindowSize(screenWidth, screenHeight);			  // set window size
	glutInitWindowPosition(100, 100);						  // set window position on screen
	glutCreateWindow("Lab 3");								  // open the screen window

	////////////////////////////////////////////////////////////////////////
	//////  INIT STATIC OBJECTS (that not changes wihtin runtime)
	////////////////////////////////////////////////////////////////////////
	//////  [!!!] DYNAMIC Objects will be initialized in mydisplay function
	////////////////////////////////////////////////////////////////////////
	crossBase.CreatCrossBase(fMainHeight, fGrooveHeight, fMainWidth, fSubWidth, fGrooveWidth, fLength);
	tieBar.CreateTrapezium(tieBar_height, tieBar_short_width, tieBar_long_width, tieBar_length);
	latchCylinderX.CreateCylinder(20, latchCylinder_height, latchCylinder_radius);
	latchCylinderZ.CreateCylinder(20, latchCylinder_height, latchCylinder_radius);
	latchCylinderCenter.CreateCylinder(20, latchCylinder_height, latchCylinder_radius);
	// Init opengl environment
	myInit();
	// Function to display main presentation
	glutDisplayFunc(myDisplay);
	// Function in idle mode
	glutIdleFunc(myIdle);
	// Setup the keyboard function triggering callback (special keyboard included)
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);

	glutMainLoop();

	return 0;
}
