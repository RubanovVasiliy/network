#include "Circle.h"
#include <cstdio>
#include <cstdlib>
#include <glut.h>

#define PI 3.14159265f
extern GLfloat ballXMax, ballXMin, ballYMax, ballYMin;

Circle::Circle() {
	this->R = (rand() % 100 / 1000.f);
	for (int angle = 0; angle < 360; angle += 1) {
		this->r_[angle] = rand() % 255;
		this->g_[angle] = rand() % 255;
		this->b_[angle] = rand() % 255;
	}

	printf("constructor Circle\n");
}

void Circle::Draw() {
	glBegin(GL_TRIANGLE_FAN);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3ub(r, g, b);
	glVertex2f(x, y);

	for (int angle = 0; angle <= 360; angle += 1) {
		float _x = R * cos(angle * PI / 180);
		float _y = R * sin(angle * PI / 180);
		glColor3ub(r_[angle], g_[angle], b_[angle]);
		glVertex2f(x + _x, y + _y);

	}
	glEnd();

}

void Circle::Move() {
	x += speedX;
	y += speedY;
	if (x + R > ballXMax) {
		speedX = -speedX;
	}
	else if (x - R < ballXMin) {
		speedX = -speedX;
	}
	if (y + R > ballYMax) {
		speedY = -speedY;
	}
	else if (y - R < ballYMin) {
		speedY = -speedY;
	}
}