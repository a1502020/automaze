#include "Hidarite.h"

Hidarite::Hidarite()
{
}

MazeAnswer Hidarite::solve(const Maze & maze)
{
	const int sx = maze.startX(), sy = maze.startY();
	const int gx = maze.goalX(), gy = maze.goalY();
	State c = { sx, sy, State::r };
	MazeAnswer res;
	res.add({ c.x, c.y });
	while (c.x != gx || c.y != gy) {
		int lx = c.x, ly = c.y, fx = c.x, fy = c.y;
		State::direction l = c.dir, r = c.dir;
		switch (c.dir)
		{
		case State::r: --ly; ++fx; l = State::u; r = State::d; break;
		case State::u: --lx; --fy; l = State::l; r = State::r; break;
		case State::l: ++ly; --fx; l = State::d; r = State::u; break;
		case State::d: ++lx; ++fy; l = State::r; r = State::l; break;
		}
		if (maze.at(lx, ly)) {
			if (maze.at(fx, fy)) {
				c.dir = r;
			}
			else {
				c.x = fx;
				c.y = fy;
				res.add({ c.x, c.y });
			}
		}
		else {
			c.x = lx;
			c.y = ly;
			c.dir = l;
			res.add({ c.x, c.y });
		}

		if (c.x == sx && c.y == sy && c.dir == State::r) {
			break;
		}
	}
	if (c.x == gx && c.y == gy) {
		return res;
	}
	else {
		return MazeAnswer();
	}
}

Hidarite::Hidarite(const Hidarite &)
{
}

const Hidarite & Hidarite::operator=(const Hidarite &)
{
	return *this;
}
