#pragma once
#include "Point.h"

class Rectanglee : public Point {
protected:
	Point point[4];
public:
	Rectanglee();
	void Draw() override;
	void Move() override;
};

