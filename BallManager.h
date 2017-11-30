#pragma once
#include "Ball.h"
#include <vector>

class BallManager
{
public:
	                  BallManager(std::vector<Ball> balls, RECT screen_);
	                  BallManager();
	                  ~BallManager();
	void              Draw();
	void              Phys();
	void			  Collider();
	void              Run();
	std::vector<Ball> balls();

private:
	void collide(Ball & a, Ball & b);

	std::vector<Ball> balls_;
	RECT screen_;
};

