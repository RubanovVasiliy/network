#pragma once
#include "Point.h"

class Line : public Point
{
protected:
	Point point[2];
public:
	Line();
	void Draw() override;
	void Move() override;
	double get_angle();
	void set_angle(double angle);
};

