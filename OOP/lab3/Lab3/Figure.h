#pragma once

class Figure
{
protected:

	double speedX;
	double speedY;
	double angle;

	int move;
	
public:
	Figure();
	virtual ~Figure();
	virtual void Draw() {}
	virtual void Move() {}
};

