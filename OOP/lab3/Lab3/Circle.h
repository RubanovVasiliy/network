#pragma once
#include "Point.h"

class Circle : public Point {
protected:
	double R;
	int r_[360];
	int g_[360];
	int b_[360];
	
public:
	Circle();
	void Draw() override;
	void Move() override;
};
