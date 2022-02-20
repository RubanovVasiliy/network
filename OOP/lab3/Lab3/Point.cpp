#include "Point.h"
#include <glut.h>
#include <vector>
#include <array>


#define PI 3.14159265f
GLfloat ballXMax, ballXMin, ballYMax, ballYMin;

using namespace std;

Point::Point() {

	this->x = (rand() % 100 / 100.f) * pow(-1, rand() % 2);
	this->y = (rand() % 100 / 100.f) * pow(-1, rand() % 2);

	this->r = rand() % 255;
	this->g = rand() % 255;
	this->b = rand() % 255;

	printf("constructor Point\n");
}

Point::~Point() {

	printf("deconstructor Point\n");
}

void Point::Draw() {

	glBegin(GL_POINTS);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3ub(r, g, b);
	glVertex2f(x, y);

	glEnd();
}

void Point::Move() {

	x += speedX;
	y += speedY;
	if (x > ballXMax) {
		x = ballXMax;
		speedX = -speedX;
	}
	else if (x < ballXMin) {
		x = ballXMin;
		speedX = -speedX;
	}
	if (y > ballYMax) {
		y = ballYMax;
		speedY = -speedY;
	}
	else if (y < ballYMin) {
		y = ballYMin;
		speedY = -speedY;
	}
}

int Point::get_r()
{
	return this->r;
}

int Point::get_g()
{
	return this->g;
}

int Point::get_b()
{
	return this->b;
}