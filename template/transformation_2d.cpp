////////////////////////////////////////////////
/////////// LAB 2D TRANSFORMATION //////////////
////////////////////////////////////////////////

#include <GL/glut.h>

#define WINDOW_LEFT -10
#define WINDOW_RIGHT 10
#define WINDOW_BOTTOM -10
#define WINDOW_TOP 10

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
}
void drawGrid()
{
    glColor3f(0.6f, 0.6f, 0.6f);
    glLineWidth(1.0);

    glBegin(GL_LINES);
    for (int i = WINDOW_LEFT; i <= WINDOW_RIGHT; i++)
    {
        glVertex2i(i, WINDOW_BOTTOM);
        glVertex2i(i, WINDOW_TOP);
    }
    for (int i = WINDOW_BOTTOM; i < WINDOW_TOP; i++)
    {
        // TODO: Code here 1
        ///////////////
        glVertex2f(WINDOW_LEFT, i);
        glVertex2f(WINDOW_RIGHT, i);
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5.0);

    glBegin(GL_LINES);
    glVertex2i(WINDOW_LEFT, 0);
    glVertex2i(WINDOW_RIGHT, 0);
    glVertex2i(0, WINDOW_BOTTOM);
    glVertex2i(0, WINDOW_TOP);
    glEnd();
}
void drawHouse()
{
    glLineWidth(3.0);
    // TODO: Code here 2
    // Drawing House
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(0, 2);
    glVertex2f(2, 4);
    glVertex2f(4, 2);
    glVertex2f(4, 0);
    glVertex2f(0, 0);
    glEnd();
    // Smokestack
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.5, 2.5);
    glVertex2f(0.5, 4);
    glVertex2f(1.5, 4);
    glVertex2f(1.5, 3.5);
    glEnd();
    // Door
    // glBegin(GL_LINE_STRIP);
    // glVertex2f(2, 0);
    // glVertex2f(2, 2);
    // glVertex2f(3, 2);
    // glVertex2f(3, 0);
    // glEnd();
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    // original form
    glColor3f(1.0f, 0.0f, 0.0f);
    drawHouse();

    // translated form
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(4, 3, 0);
    drawHouse();
    glPopMatrix();

    // scaled form (and translated)
    glPushMatrix();
    glColor3f(1, 0.5, 1);
    glScalef(1, 1.5, 1);
    glTranslatef(2, -2, 0);
    drawHouse();
    glPopMatrix();

    // rotated form and translated
    glPushMatrix();
    glColor3f(1, 0.5, 0.5);
    glRotatef(90, 0, 0, 1);
    glTranslatef(2, 0, 0);
    drawHouse();
    glPopMatrix();

    // rotated form and scaled
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2);
    glScalef(1.5, 1.5, 1);
    glRotatef(180, 0, 0, 1);
    drawHouse();
    glPopMatrix();

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, (char **)argv);              // initialize the tool kit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
    glutInitWindowSize(650, 650);                // set window size
    glutInitWindowPosition(0, 0);                // set window position on screen
    glutCreateWindow("LAB - 2D Transformation");      // open the screen window

    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}
