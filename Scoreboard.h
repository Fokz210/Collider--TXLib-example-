#pragma once
#include "TXLib.h"
#include "Ball.h"

struct SCORECELL
{
	DPOINT pos;
	int score;
	COLORREF color;
};

class Scoreboard
{
public:
	            Scoreboard(int BALLS_COUNT);
	            ~Scoreboard();
	void        Run();
	void        refresh(std::vector<Ball> ball);

private:
	void        draw();

	int         BALLS_COUNT_;
	int         CELL_COUNT_;
	SCORECELL * arr_;
};


