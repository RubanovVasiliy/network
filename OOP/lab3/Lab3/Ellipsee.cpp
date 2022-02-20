#include "Ellipsee.h"
#include <cstdio>
#include <cstdlib>
#include <glut.h>

#define PI 3.14159265f
extern GLfloat ballXMax, ballXMin, ballYMax, ballYMin;

Ellipsee::Ellipsee() {
	this->R_min = (rand() % 90 / 1000.f);
	
	printf("constructor Ellipse\n");
}

void Ellipsee::Draw() {
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(static_cast<GLbyte>(Point::get_r()),
		static_cast<GLbyte>(Point::get_g()),
		static_cast<GLbyte>(Point::get_b()));
	glVertex2f(x, y);
	for (int angle = 0; angle <= 360; angle += 1)
	{
		float a = (fabsf(angle - float(2 * PI)) < 0.00001f) ? 0.f : angle;
		const auto dx = R * cosf(a);
		const auto dy = R_min * sinf(a);
		glColor3ub(r_[angle], g_[angle], b_[angle]);
		glVertex2f(dx + x, dy + y);
	}
	glEnd();
	glPopMatrix();
}

void Ellipsee::Move() {
	x += speedX;
	y += speedY;
	if (x + R > ballXMax) {
		speedX = -speedX;
	}
	else if (x - R < ballXMin) {
		speedX = -speedX;
	}
	if (y + R_min > ballYMax) {
		speedY = -speedY;
	}
	else if (y - R_min < ballYMin) {
		speedY = -speedY;
	}
}
