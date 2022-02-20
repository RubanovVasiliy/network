#pragma once
#include "Line.h"
#include "Figure.h";
#include "Point.h";
#include <windows.h>
#include <glut.h>
#include <vector>
#include <array>


#define PI 3.14159265f
extern GLfloat ballXMax, ballXMin, ballYMax, ballYMin;

Line::Line() {
	this->point[0].x = rand() % 500 / 1000.f;
	this->point[0].y = rand() % 500 / 1000.f;
	
	
	this->point[1].x = rand() % 500 / 1000.f;
	this->point[1].y = rand() % 500 / 1000.f;

	printf("constructor Line\n");
}

double Line::get_angle()
{
	return this->angle;
}

void Line::set_angle(double angle)
{
	this->angle = angle;
}

void Line::Draw()
{
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3ub(point[0].r, point[0].g, point[0].b);
	glVertex2d(point[0].x, point[0].y);
	glColor3ub(point[1].r, point[1].g, point[1].b);
	glVertex2d(point[1].x, point[1].y);
	glEnd();
	glPopMatrix();
}

void Line::Move() {
	point[0].x += speedX;
	point[0].y += speedY;
	point[1].x += speedX;
	point[1].y += speedY;

	if (point[0].x > ballXMax || point[1].x > ballXMax) {
		speedX = -speedX;
	}
	else if (point[0].x < ballXMin || point[1].x < ballXMin) {
		speedX = -speedX;
	}
	if (point[0].y > ballYMax || point[1].y > ballYMax) {
		speedY = -speedY;
	}
	else if (point[0].y < ballYMin || point[1].y < ballYMin) {
		speedY = -speedY;
	}
}