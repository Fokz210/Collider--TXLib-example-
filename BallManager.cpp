#include "BallManager.h"
#include "Globals.h"

BallManager::BallManager()
{

}

BallManager::BallManager(std::vector<Ball> Balls, RECT screen) :
	balls_(Balls),
	screen_(screen)
{
}

BallManager::~BallManager()
{

}

void BallManager::Draw()
{
	for (unsigned int i = 0; i < balls_.size(); i++)
		balls_[i].Draw();
}

void BallManager::Phys()
{
	for (unsigned int i = 0; i < balls_.size(); i++)
		balls_[i].Physics(screen_);
}

void BallManager::Collider()
{
	for (unsigned int i = 0; i < balls_.size(); i++)
		for (unsigned int j = i; j < balls_.size(); j++)
		{
			if (i == j) continue;

			if (sqrt((balls_[i].pos().x() - balls_[j].pos().x())*(balls_[i].pos().x() - balls_[j].pos().x()) + ((balls_[i].pos().y() - balls_[j].pos().y()) * (balls_[i].pos().y() - balls_[j].pos().y()))) < balls_[i].radius() + balls_[j].radius() &&
				VectorsAngleCos(balls_[i].vel() - balls_[j].vel(), balls_[i].pos() - balls_[j].pos()) <= 0)
			{
				collide(balls_[i], balls_[j]);
			}
		}
}

void BallManager::Run()
{
	Draw();
	Phys();
	Collider();
}

std::vector<Ball> BallManager::balls()
{
	return balls_;
}

void BallManager::collide(Ball & a, Ball & b)
{
	MathVector p1 = a.vel() * a.radius(), p2 = b.vel() * b.radius();

	/* 1)   */ MathVector n = MathVector(a.pos() - b.pos()).norm();
	/* 2)   */ MathVector t(-n.y(), n.x());
	/* 3.1) */ double p1n = p1 * n, p2n = p2 * n;
	/* 4.1) */ double buff = p1n;
	/* 4.2) */ p1n = p2n;
	/* 4.3) */ p2n = buff;
	/* 5)   */ MathVector p1ns = n * p1n, p2ns = n * p2n;
	/* 6)   */ MathVector p1t = t * (p1 * t), p2t = t * (p2 * t);
	/* 7)   */ MathVector p1s = p1ns + p1t, p2s = p2ns + p2t;

	a.vel(p1s / a.radius());
	b.vel(p2s / b.radius());

	if (DEBUG_)
	{
			MathVector(a.pos() - b.pos()).Visualise(b.pos().x(), b.pos().y(), 1, TX_GRAY, 1, "O1O2");

			MathVector(n * p2n).Visualise(a.pos().x(), a.pos().y(), 0.003, TX_RED, 2, "p1n");
			MathVector(n * p1n).Visualise(b.pos().x(), b.pos().y(), 0.003, TX_RED, 2, "p2n");
			p1t.Visualise(a.pos().x(), a.pos().y(), 0.003, TX_GREEN, 2, "p1t");
			p2t.Visualise(b.pos().x(), b.pos().y(), 0.003, TX_GREEN, 2, "p2t");
			p1ns.Visualise(a.pos().x(), a.pos().y(), 0.003, TX_RED, 2, "p1n'");
			p2ns.Visualise(b.pos().x(), b.pos().y(), 0.003, TX_RED, 2, "p2n'");


			p1s.Visualise(a.pos().x(), a.pos().y(), 0.003, TX_ORANGE, 2, "p1'");
			p2s.Visualise(b.pos().x(), b.pos().y(), 0.003, TX_ORANGE, 2, "p2'");


			n.Visualise(600, 100, 100, TX_RED, 2, "n");
			t.Visualise(600, 100, 100, TX_GREEN, 2, "t");
		}
}
