#include "Rhombus.h"
#include <cstdio>
#include <cstdlib>
#include <glut.h>

extern GLfloat ballXMax, ballXMin, ballYMax, ballYMin;

Rhombus::Rhombus() {
	float temp_x_1 = rand() % 100 / 1000.f;
	float temp_y_1 = rand() % 100 / 1000.f;

	this->point[0].x = -temp_x_1;
	this->point[0].y = 0;

	this->point[1].x = 0;
	this->point[1].y = temp_y_1;

	this->point[2].x = temp_x_1;
	this->point[2].y = 0;

	this->point[3].x = 0;
	this->point[3].y = -temp_y_1;

	printf("constructor Rhombus\n");
}

void Rhombus::Draw()
{
	glPushMatrix();

	glBegin(GL_QUADS);
	glColor3ub(point[0].r, point[0].g, point[0].b);
	glVertex2d(point[0].x, point[0].y);
	glColor3ub(point[1].r, point[1].g, point[1].b);
	glVertex2d(point[1].x, point[1].y);
	glColor3ub(point[2].r, point[2].g, point[2].b);
	glVertex2d(point[2].x, point[2].y);
	glColor3ub(point[3].r, point[3].g, point[3].b);
	glVertex2d(point[3].x, point[3].y);
	glEnd();
	glPopMatrix();
}

void Rhombus::Move() {
	point[0].x += speedX;
	point[0].y += speedY;
	point[1].x += speedX;
	point[1].y += speedY;
	point[2].x += speedX;
	point[2].y += speedY;
	point[3].x += speedX;
	point[3].y += speedY;

	if (point[0].x > ballXMax || point[1].x > ballXMax || point[2].x > ballXMax || point[3].x > ballXMax) {
		speedX = -speedX;
	}
	else if (point[0].x < ballXMin || point[1].x < ballXMin || point[2].x < ballXMin || point[3].x < ballXMin) {
		speedX = -speedX;
	}
	if (point[0].y > ballYMax || point[1].y > ballYMax || point[2].y > ballYMax || point[3].y > ballYMax) {
		speedY = -speedY;
	}
	else if (point[0].y < ballYMin || point[1].y < ballYMin || point[2].y < ballYMin || point[3].y < ballYMin) {
		speedY = -speedY;
	}
}