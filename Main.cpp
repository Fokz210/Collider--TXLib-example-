#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#include "TXLib.h"
#include "Ball.h"
#include "BallManager.h"
#include "Scoreboard.h"
#include "Globals.h"

void MusicSwitch(const char * fileName, char button);
void DebugSwitch(char button);
void ShakeSwitch(char button);

int main()
{

	txDisableAutoPause();
	txCreateWindow(1366, 768);
	txBegin();

	srand((unsigned int)time(0));

	std::vector<Ball> balls;

	HDC anim = txLoadImage("bin//animation.bmp");
	HDC background = txLoadImage("bin//background.bmp");

	for (int i = 0; i < 10; i++)
	{
		Ball example(400, 70 + rand() % 10, { anim, {50, 50}, 14 });
		balls.push_back(example);
	}

	BallManager manager(balls, { txGetExtentX() / 5 + txGetExtentX() / 200, 0, txGetExtentX(), txGetExtentY() });

	Scoreboard scoreboard(balls.size());
	txSelectFont("Calibri Light", 25);

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		MusicSwitch("bin//stars.wav", 'M');
		DebugSwitch('D');
		ShakeSwitch('S');

		manager.Run();

		if (!DEBUG_)
		{
            scoreboard.refresh(manager.balls());
            scoreboard.Run();
            txSetColor(RGB(161, 2, 219));
            txSetFillColor(RGB(161, 2, 219));
            txRectangle(txGetExtentX() / 5, 0, txGetExtentX() / 5 + txGetExtentX() / 200, txGetExtentY());
        }

        txSetColor(TX_LIGHTGREEN);

		txDrawText(txGetExtentX() / 10 * 7, 10, txGetExtentX(), 100, "[D] - Отладка (Любая клавиша для следующей итерации)\n[S] - Режим \"Шейкер\"\n[M] - Музыка вкл\\выкл");

		if (DEBUG_) _getch();

		txSetFillColor(TX_WHITE);
		txSleep(10);
		txClear();
		if (background && !DEBUG_) txBitBlt(txDC(), 0, 0, 1366, 768, background);
	}

	txDeleteDC(background);
	return EXIT_SUCCESS;
}

void Ball::Draw()
{
	static int counter = 0;

	if (globalCounter_ % 3 == 0) counter++;
	globalCounter_++;

	txSetColor(color_);
	txSetFillColor(color_);

	txCircle(pos_.x(), pos_.y(), radius_);

	if (DEBUG_) vel_.Visualise(pos_.x(), pos_.y(), 0.003 * radius_, TX_BLUE, 2, "p");

	if (anim_.anim) txTransparentBlt(txDC(), pos_.x() - radius_, pos_.y() - radius_, anim_.size.x, anim_.size.y, anim_.anim, anim_.size.x * (counter % anim_.framesCount), 0, TX_WHITE);
}

void Scoreboard::draw()
{
	char *buff = new char[32];
	for (int i = 0; i < ((BALLS_COUNT_ <= 20) ? BALLS_COUNT_ : 20); i++)
	{
		txSetColor(arr_[i].color);
		txSetFillColor(arr_[i].color);

		txRectangle(0, txGetExtentY() / 20 * i, txGetExtentX() / 5, txGetExtentY() / 20 * i + txGetExtentY() / 20);

		txSetColor(TX_WHITE);

		sprintf(buff, "#%d    Score: %d.", i + 1, arr_[i].score);
		txDrawText(0, i * txGetExtentY() / 20, txGetExtentX() / 5, i * txGetExtentY() / 20 + txGetExtentY() / 20, buff);
	}
	delete(buff);
}

MathVector MathVector::Visualise(double x, double y, double k, COLORREF color, int thickness, const char * name)
{
	txSetFillColor(color);
	txSetColor(color, thickness);

	txLine(x, y, x + val.x * k, y + val.y * k);

	txCircle(x + val.x * k, y + val.y * k, 3);

	txSelectFont("Calibri", 24);
	txTextOut(x + val.x * k, y + val.y * k, name);

	return *this;
}

Ball::Ball() :
	pos_(rand() % txGetExtentX(), rand() % txGetExtentY()),
	vel_(),
	radius_(0),
	color_(RGB(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55)),
	score_(0),
	org0({ 0, 0 }),
	org1({ 0, 0 })
{

}

Ball::Ball(double maxVelocity, int radius) :
	pos_(rand() % txGetExtentX(), rand() % txGetExtentY()),
	vel_(rand() % (int)(maxVelocity * 2) - maxVelocity, rand() % (int)(maxVelocity * 2) - maxVelocity),
	radius_(radius),
	color_(RGB(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55)),
	score_(0),
	org0({ 0, 0 }),
	org1({ 0, 0 })
{
}

Ball::Ball(double maxVelocity, int radius, ANIMATION Anim) :
	pos_(rand() % txGetExtentX(), rand() % txGetExtentY()),
	vel_(rand() % (int)(maxVelocity * 2) - maxVelocity, rand() % (int)(maxVelocity * 2) - maxVelocity),
	radius_(radius),
	color_(RGB(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55)),
	anim_(Anim),
	globalCounter_(0),
	score_(0),
	org0({ 0, 0 }),
	org1({ 0, 0 })
{
}

void Ball::VelRedefine()
{
	static MathVector newVel;
	static bool wasPressed = false;

	printf("%f, %f    \r", newVel.x(), newVel.y());


	if (wasPressed)
	{
		newVel.x(txMouseX() - newVel.x());
		newVel.y(txMouseY() - newVel.y());
		printf("\a");
		vel_ = newVel * 10;
		wasPressed = false;
	}
	else if (!wasPressed)
	{
		wasPressed = true;
		newVel.setVal(txMousePos());
	}
}

void MusicSwitch(const char * fileName, char button)
{
	static bool buttonClick = false;
	static bool music = false;

	if (GetAsyncKeyState(button) && !music && !buttonClick)
	{
		buttonClick = true;
		music = true;
		txPlaySound(fileName, SND_LOOP);
		printf("\a");
	}
	else if (GetAsyncKeyState(button) && music && !buttonClick)
	{
		buttonClick = true;
		music = false;
		txPlaySound(NULL);
	}
	else if (!GetAsyncKeyState(button))
	{
		buttonClick = false;
	}
}

void DebugSwitch(char button)
{
	static bool buttonClick = false;

	if (GetAsyncKeyState(button) && !DEBUG_ && !buttonClick)
	{
		buttonClick = true;
		DEBUG_ = true;
		printf("\a");
	}
	else if (GetAsyncKeyState(button) && DEBUG_ && !buttonClick)
	{
		buttonClick = true;
		DEBUG_ = false;
	}
	else if (!GetAsyncKeyState(button))
	{
		buttonClick = false;
	}
}

void ShakeSwitch(char button)
{
	static bool buttonClick = false;

	if (GetAsyncKeyState(button) && !SHAKE && !buttonClick)
	{
		buttonClick = true;
		SHAKE = true;
		printf("\a");
	}
	else if (GetAsyncKeyState(button) && SHAKE && !buttonClick)
	{
		buttonClick = true;
		SHAKE = false;
	}
	else if (!GetAsyncKeyState(button))
	{
		buttonClick = false;
	}
}

POINT TxGetWindowOrg()
{
	RECT r = { 0, 0, 0, 0 };
	GetWindowRect(txWindow(), &r);
	POINT org = { r.left, r.top };
	return org;
}
