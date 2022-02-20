#pragma once
#include "Triangle.h"
#include "Point.h"
#include <glut.h>
#include <vector>
#include <array>


extern GLfloat ballXMax, ballXMin, ballYMax, ballYMin;

Triangle::Triangle() {
	this->point[0].x = 0.03 + x;
	this->point[0].y = -0.25 + y;

	this->point[1].x = 0.30 + x;
	this->point[1].y = -0.25 + y;

	this->point[2].x = 0.15 + x;
	this->point[2].y = -0.03 + y;

	printf("constructor Triangle\n");
}

double Triangle::get_angle()
{
	return this->angle;
}

void Triangle::set_angle(double angle)
{
	this->angle = angle;
}

void Triangle::Draw()
{
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(point[0].r, point[0].g, point[0].b);
	glVertex2d(point[0].x, point[0].y);
	glColor3ub(point[1].r, point[1].g, point[1].b);
	glVertex2d(point[1].x, point[1].y);
	glColor3ub(point[2].r, point[2].g, point[2].b);
	glVertex2d(point[2].x, point[2].y);
	glEnd();
	glPopMatrix();
}

void Triangle::Move() {
	point[0].x += speedX;
	point[0].y += speedY;
	point[1].x += speedX;
	point[1].y += speedY;
	point[2].x += speedX;
	point[2].y += speedY;

	if (point[0].x > ballXMax || point[1].x > ballXMax || point[2].x > ballXMax) {
		speedX = -speedX;
	}
	else if (point[0].x < ballXMin || point[1].x < ballXMin || point[2].x < ballXMin) {
		speedX = -speedX;
	}
	if (point[0].y > ballYMax || point[1].y > ballYMax || point[2].y > ballYMax) {
		speedY = -speedY;
	}
	else if (point[0].y < ballYMin || point[1].y < ballYMin || point[2].y < ballYMin) {
		speedY = -speedY;
	}
}