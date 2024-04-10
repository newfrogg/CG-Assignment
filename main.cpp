#include <math.h>
#include <iostream>
#include <vector>
#include "supportClass.h"
#include "Mesh.h"

#define DEG2RAD(x) (x * M_PI) / 180.0f

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
colorMode e_colorMode = Colored;
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
float latchCylinder_height = fMainHeight - fGrooveHeight + 0.2;
// SLIDER X / Z
float slider_height = fMainHeight - fGrooveHeight;
float slider_width = fGrooveWidth;
float slider_length = 1; // FLength / 5

float sliderMax_pos = 4;
float m_angle = 45;
float sliderX_pos = 4 * cos(m_angle * M_PI / 180);
float sliderZ_pos = 4 * sin(m_angle * M_PI / 180);

// Local camera papameter
float m_angleX = 0;
float m_angleZ = 0;

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
		camera_X, camera_Y, camera_Z,
		0, 0, 0,
		0, 1, 0);
	// Clear buffers to prepare for rendering new frame
	// just only glEnable(GL_DEPTH_TEST) have been enabled before so that the following for depth need being called
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// gl view port which set port of view in the current screen
	glViewport(0, 0, screenWidth, screenHeight);
	{
		/// ALLOW ROTATE AROUND ITS STRUCTURE AXIS 
		/// local x-axis map to axis-X in real world
		/// local y-axis map to axis-Z in real world
		/// The height is always the axis-Y
		/// CHANGE MODE BETWEEN DRAW COLORED OR WIREFRAME IS ALSO ALLOWED.
		glPushMatrix();
		glRotatef(m_angleX, 1, 0, 0);
		glRotatef(m_angleZ, 0, 0, 1);

		// Display Main CrossBar
		glColor3f(0, 0, 1);
		e_colorMode == Colored ? crossBase.DrawColorCrossBase() : crossBase.DrawWireframe();
		// Display the Tie bar (connecting object)
		glPushMatrix();
		glTranslatef(0, fMainHeight + tieBar_height, 0);
		glTranslatef(sliderX_pos / 2, 0, sliderZ_pos / 2);
		glRotatef(m_angle, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		e_colorMode == Colored ? tieBar.DrawColorTieBar() : tieBar.DrawWireframe();
		glPopMatrix();
		// Display 3 latch cylinder
		glPushMatrix();
		glTranslatef(0, latchCylinder_height / 2 + 0.2, 0);
		glTranslatef(sliderX_pos, fGrooveHeight, 0);
		e_colorMode == Colored ? latchCylinderX.DrawColorLatchCylinder() : latchCylinderX.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, latchCylinder_height / 2 + 0.2, 0);
		glTranslatef(0, fGrooveHeight, sliderZ_pos);
		e_colorMode == Colored ? latchCylinderZ.DrawColorLatchCylinder() : latchCylinderZ.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, latchCylinder_height / 2 + fMainHeight + 0.01, 0);
		glTranslatef(sliderX_pos / 2, 0, sliderZ_pos / 2);
		e_colorMode == Colored ? latchCylinderCenter.DrawColorLatchCylinder() : latchCylinderCenter.DrawWireframe();
		glPopMatrix();
		// Display 2 slider
		glPushMatrix();
		glScalef(slider_length, slider_height, slider_width);
		glTranslatef(0, fMainHeight, 0);
		glTranslatef(sliderX_pos, fGrooveHeight, 0);
		e_colorMode == Colored ? sliderX.DrawColorSlider() : sliderX.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		glScalef(slider_width, slider_height, slider_length);
		glTranslatef(0, fMainHeight, 0);
		glTranslatef(0, fGrooveHeight, sliderZ_pos);
		e_colorMode == Colored ? sliderZ.DrawColorSlider() : sliderZ.DrawWireframe();
		glPopMatrix();
		glPopMatrix();
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////// END OF VIEW PORT ///////////////////////////////////////////////// 
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

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
		exit(0);
		break;
	case 'w':
	case 'W':
		e_colorMode = (e_colorMode == Wired) ? Colored : Wired;
		break;
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
		camera_dis += 0.2f;
		changeCameraPos();
		break;
	case '-':
		camera_dis -= 0.2f;
		changeCameraPos();
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
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.6f;
		changeCameraPos();
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.6f;
		changeCameraPos();
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 0.6f;
		changeCameraPos();
		break;
	case GLUT_KEY_LEFT:
		camera_angle -= 0.6f;
		changeCameraPos();
		break;
	default:
		// Handle other keys if needed
		break;
	}
	printf("[LOG:::BUTTON] button[%c] is pressed.\n", key);
	glutPostRedisplay();
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

	camera_angle = 45;
	camera_height = 4;
	camera_dis = 4.5;
	camera_X = sin(DEG2RAD(camera_angle)) * camera_dis;
	camera_Y = camera_height;
	camera_Z = cos(DEG2RAD(camera_angle)) * camera_dis;
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
	sliderX.CreateCube(0.5);
	sliderZ.CreateCube(0.5);
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
