#pragma once
#include "Point.h"
class Triangle : public Point
{
protected:
	Point point[3];
public:
	double get_angle();
	void set_angle(double angle);
	Triangle();
	void Draw() override;
	void Move() override;
};

