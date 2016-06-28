#include "Migite.h"

Migite::Migite()
{
}

MazeAnswer Migite::solve(const Maze & maze)
{
	const int sx = maze.startX(), sy = maze.startY();
	const int gx = maze.goalX(), gy = maze.goalY();
	State c = { sx, sy, State::d };
	MazeAnswer res;
	res.add({ c.x, c.y });
	while (c.x != gx || c.y != gy) {
		int rx = c.x, ry = c.y, fx = c.x, fy = c.y;
		State::direction l, r;
		switch (c.dir)
		{
		case State::r: ++ry; ++fx; l = State::u; r = State::d; break;
		case State::u: ++rx; --fy; l = State::l; r = State::r; break;
		case State::l: --ry; --fx; l = State::d; r = State::u; break;
		case State::d: --rx; ++fy; l = State::r; r = State::l; break;
		}
		if (maze.at(rx, ry)) {
			if (maze.at(fx, fy)) {
				c.dir = l;
			}
			else {
				c.x = fx;
				c.y = fy;
				res.add({ c.x, c.y });
			}
		}
		else {
			c.x = rx;
			c.y = ry;
			c.dir = r;
			res.add({ c.x, c.y });
		}

		if (c.x == sx && c.y == sy && c.dir == State::d) {
			break;
		}
	}
	if (c.x == gx && c.y == gy || true) {
		return res;
	}
	else {
		return MazeAnswer();
	}
}

Migite::Migite(const Migite &)
{
}

const Migite & Migite::operator=(const Migite &)
{
	return *this;
}
