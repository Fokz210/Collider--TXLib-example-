#pragma once
#include "TXLib.h"
#include "MathVector.h"
#include "Globals.h"

const MathVector g (0, 9.815);
const double     DT = 0.01;

POINT TxGetWindowOrg();

struct ANIMATION
{
	HDC    anim;
	DPOINT size;
	int    framesCount;
};

class Ball
{
public:
	           Ball();
	           Ball(double maxVelocity, int radius);
	           Ball(double maxVelocity, int radius, ANIMATION Anim);
	           ~Ball();
	void       Draw();
	void       Physics(RECT screen);
	int        score();
	int		   radius();
	void       radius(int rad);
	COLORREF   color();
	MathVector pos();
	MathVector vel();
	void	   vel(MathVector vel);
	void	   VelRedefine();
	void       BackupPos() { pos_ = prevPos_; }

protected:
	MathVector pos_;
	MathVector prevPos_;
	MathVector vel_;
	int        radius_;
	COLORREF   color_;
	ANIMATION  anim_;
	int        globalCounter_;
	int        score_;
	POINT      org0;
	POINT      org1;
};

