#pragma once
#include "Circle.h"

class Ellipsee : public Circle {
protected:
	double R_min;
public:
	Ellipsee();
	void Draw() override;
	void Move() override;
};
