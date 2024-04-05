#include <math.h>
#include <GL/glut.h>

const int screenWidth = 650;
const int screenHeight = 650;
//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// CHU Y /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
// Cac buoc dieu chinh anh sang cho 1 doi tuong										//
// 1. Thiet lap nguon sang: 														//
// 		- thiet lap vi tri dat nguon sang											//
// 		- thiet lap anh sang khuech tan (diffuse)									//
// 		- thiet lap anh sang phan chieu (specular)									//
// 2. Thiet lap vat lieu doi tuong (duoc chieu sang)								//
// 		- thiet lap anh sang khuech tan: phai tuong ung voi nguon sang thi			//
// 		anh sang tu nguon sang moi khuyech tan len be mat vat lieu					//
// 		vi du: light_diffuse (r,g,b) = < 0.2, 0.6, 0.68>							//
//		ma material_diffuse (r,g,b) = < 0.95, 0.0, 1>								//
// 		thi phan anh sang BLUE cua nguon sang dc khuech tan nhieu nhat				//	
// 		tiep den len phan anh sang RED thap hon (1 > 0.95)							//
// 		phan anh sang GREEN bi suy bien thanh 0 (bien mat)							//
// 		- thiet lap anh sang phan chieu: tuong tu nhu tren.							//
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
}
void setLight()
{
	const GLfloat leftLightDiffColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
	const GLfloat leftLightSpecColor[] = {1.0f, 0.75f, 0.0f, 1.0f};
	const GLfloat leftLightAmbColor[] = {0.1f, 0.1f, 0.1f, 1.0f};
	const GLfloat leftLightPos[] = {-5.0, 0.0, 0.0, 0.0};

	const GLfloat rightLightDiffColor[] = {0.0f, 0.0f, 1.0f, 1.0f};
	const GLfloat rightLightSpecColor[] = {0.54, 0.17, 0.89, 1.0f};
	const GLfloat rightLightAmbColor[] = {0.1f, 0.1f, 0.1f, 1.0f};
	const GLfloat rightLightPos[] = {5.0, 0.0, 0.0, 0.0};

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	// set up right light
	glLightfv(GL_LIGHT0, GL_POSITION, rightLightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, rightLightAmbColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, rightLightDiffColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, rightLightSpecColor);
	glEnable(GL_LIGHT0);

	// set up left light
	glLightfv(GL_LIGHT1, GL_POSITION, leftLightPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, leftLightAmbColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, leftLightDiffColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, leftLightSpecColor);
	glEnable(GL_LIGHT1);
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setLight();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0f};
	GLfloat diffuse[] = {1.0, 0.0, 1.0, 1.0f};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0f};
	GLfloat shiness = 100.8;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);

	glutSolidSphere(1.0, 100, 100);

	glutSwapBuffers();
	glFlush();

	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, (char **)argv);							  // initialize the tool kit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // set the display mode
	glutInitWindowSize(screenWidth, screenHeight);			  // set window size
	glutInitWindowPosition(0, 0);							  // set window position on screen
	glutCreateWindow("Lab Lighting - Bai 2");				  // open the screen window

	glutDisplayFunc(display);

	init();
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}