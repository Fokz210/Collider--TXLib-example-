#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include "Scoreboard.h"

Scoreboard::Scoreboard(int BALLS_COUNT) :
	BALLS_COUNT_(BALLS_COUNT),
	CELL_COUNT_((BALLS_COUNT <= 20) ? BALLS_COUNT : 20),
	arr_(new SCORECELL[BALLS_COUNT])
{
}

Scoreboard::~Scoreboard()
{
	delete(arr_);
}

void QuickSort(SCORECELL data[], int Size, int Left, int Right);
void Swap(SCORECELL balls[], int a, int b);
void REV(SCORECELL data[], int size);

void Scoreboard::Run()
{
	QuickSort(arr_, BALLS_COUNT_, 0, BALLS_COUNT_ - 1);
	REV(arr_, BALLS_COUNT_);

	draw();
}

void Scoreboard::refresh(std::vector<Ball> ball)
{
	BALLS_COUNT_ = ball.size();

	for (int i = 0; i < BALLS_COUNT_; i++)
	{
		arr_[i].score = ball[i].score();
		arr_[i].pos = ball[i].pos().pointValue();
		arr_[i].color = ball[i].color();
	}
}

void QuickSort(SCORECELL data[], int Size, int Left, int Right);

void Swap(SCORECELL balls[], int a, int b);

void REV(SCORECELL data[], int size);

void QuickSort(SCORECELL data[], int Size, int Left, int Right)
{
	int mid = (Left + Right) / 2;
	int x = Left;
	int y = Right;

	while (x <= y)
	{
		while (data[x].score < data[mid].score)
		{
			x++;
		}

		while (data[y].score > data[mid].score)
		{
			y--;
		}

		if (x <= y)
		{
			Swap(data, x, y);
			x++;
			y--;
		}
	}

	if (x < Right)
	{
		QuickSort(data, Size, x, Right);
	}

	if (y > Left)
	{
		QuickSort(data, Size, Left, y);
	}
}

void Swap(SCORECELL balls[], int a, int b)
{
	SCORECELL buff = balls[a];
	balls[a] = balls[b];
	balls[b] = buff;
}

void REV(SCORECELL data[], int size)
{
	for (int i = 0; i < size / 2; i++)
	{
		Swap(data, i, size - i - 1);
	}
}

