#include <glut.h>
#include <vector>
#include <array>
#include <vector>
#include <ctime>
#include "Point.h"
#include "Figure.h"
#include "Line.h"
#include "Triangle.h"
#include "Circle.h"
#include "Ellipsee.h"
#include "Rectanglee.h"
#include "Rhombus.h"


using namespace std;

extern GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
extern float ballRadius = 0.007f;
// Global variables

char title[] = "Bouncing Ball (2D)";
int windowWidth = 640;
int windowHeight = 480;
int windowPosX = 50;
int windowPosY = 50;
int refreshMillis = 30;

bool fullScreenMode = true;

GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

vector<Figure*> figures;

void initGL() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (auto* item : figures) {
		item->Draw();
		item->Move();
	}

	glutSwapBuffers();

}

void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width >= height) {
		clipAreaXLeft = -1.0 * aspect;
		clipAreaXRight = 1.0 * aspect;
		clipAreaYBottom = -1.0;
		clipAreaYTop = 1.0;
	}

	else {
		clipAreaXLeft = -1.0;
		clipAreaXRight = 1.0;
		clipAreaYBottom = -1.0 / aspect;
		clipAreaYTop = 1.0 / aspect;
	}
	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	ballXMin = clipAreaXLeft + ballRadius;
	ballXMax = clipAreaXRight - ballRadius;
	ballYMin = clipAreaYBottom + ballRadius;
	ballYMax = clipAreaYTop - ballRadius;

}

void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(refreshMillis, Timer, 0);
}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 27: // ESC key
		exit(0);
		break;
	}
}

void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:    // F1: Toggle between full-screen and windowed mode
		fullScreenMode = !fullScreenMode;         // Toggle state
		if (fullScreenMode) {                     // Full-screen mode
			windowPosX = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later
			windowPosY = glutGet(GLUT_WINDOW_Y);
			windowWidth = glutGet(GLUT_WINDOW_WIDTH);
			windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();                      // Switch into full screen
		}
		else {                                         // Windowed mode
			glutReshapeWindow(windowWidth, windowHeight); // Switch into windowed mode
			glutPositionWindow(windowPosX, windowPosY);   // Position top-left corner
		}
		break;
	}
}

int main(int argc, char** argv) {

	srand(time(NULL));

	for (int i = 0; i < 50; ++i) {
		figures.push_back(new Point());
		figures.push_back(new Line());
		figures.push_back(new Triangle());
		figures.push_back(new Circle());
		figures.push_back(new Ellipsee());
		figures.push_back(new Rectanglee());
		figures.push_back(new Rhombus());

	}
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(windowWidth, windowHeight); // Initial window width and height
	glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
	glutCreateWindow(title); // Create window with given title
	glutDisplayFunc(display); // Register callback handler for window re-paint
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);// Register callback handler for window re-shape
	glutSpecialFunc(specialKeys);
	glutTimerFunc(0, Timer, 0); // First timer call immediately
	glutFullScreen(); // Put into full screen
	initGL(); // Our own OpenGL initialization
	glutMainLoop(); // Enter event-processing loop

	return 0;

}