#include <math.h>
#include <GL/glut.h>

const int screenWidth = 650;
const int screenHeight = 650;

GLfloat mat_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat mat_diffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat_shininess[] = {50.0f};

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
}
void setLight()
{
	GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat lightDiffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat light_position[] = {2, 1, 2, 0.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);
}
void setMaterial()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}
void setCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(2, 1, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void drawAxis()
{
	glDisable(GL_LIGHTING);

	float xmax = 1.0, ymax = 1.0, zmax = 1.0;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(-xmax, 0, 0);
	glVertex3f(xmax, 0, 0);
	glVertex3f(0, -ymax, 0);
	glVertex3f(0, ymax, 0);
	glVertex3f(0, 0, -zmax);
	glVertex3f(0, 0, zmax);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;

	glRasterPos3f(1.0, 0, 0);
	glutBitmapCharacter(font, 'X');

	glRasterPos3f(0, 1.0, 0);
	glutBitmapCharacter(font, 'Y');

	glRasterPos3f(0, 0, 1.0);
	glutBitmapCharacter(font, 'Z');
}
void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setCamera();
	drawAxis();
	setLight();

	setMaterial();

	glutSolidTeapot(0.5);

	glFlush();
}
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1': // Nhua den
		mat_ambient[0] = 0;
		mat_ambient[1] = 0;
		mat_ambient[2] = 0;

		mat_diffuse[0] = 0.01;
		mat_diffuse[1] = 0.01;
		mat_diffuse[2] = 0.01;

		mat_specular[0] = 0.5;
		mat_specular[1] = 0.5;
		mat_specular[2] = 0.5;

		mat_shininess[0] = 32;
		break;
	case '7': // Vang
		mat_ambient[0] = 0.24725;
		mat_ambient[1] = 0.1995;
		mat_ambient[2] = 0.0745;

		mat_diffuse[0] = 0.75164;
		mat_diffuse[1] = 0.60648;
		mat_diffuse[2] = 0.22648;

		mat_specular[0] = 0.628281;
		mat_specular[1] = 0.555802;
		mat_specular[2] = 0.366065;

		mat_shininess[0] = 51.2;
		break;
	case '9': // Bac
		mat_ambient[0] = 0.19225;
		mat_ambient[1] = 0.19225;
		mat_ambient[2] = 0.19225;

		mat_diffuse[0] = 0.50754;
		mat_diffuse[1] = 0.50754;
		mat_diffuse[2] = 0.50754;

		mat_specular[0] = 0.508273;
		mat_specular[1] = 0.508273;
		mat_specular[2] = 0.508273;

		mat_shininess[0] = 51.2;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, (char **)argv);							  // initialize the tool kit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // set the display mode
	glutInitWindowSize(screenWidth, screenHeight);			  // set window size
	glutInitWindowPosition(0, 0);							  // set window position on screen
	glutCreateWindow("Lab Lighting");						  // open the screen window
	glutKeyboardFunc(myKeyboard);

	glutDisplayFunc(display);

	init();
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}