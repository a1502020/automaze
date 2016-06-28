#pragma once

#include "MazeSolver.h"

class Migite : public MazeSolver {
public:
	Migite();

	MazeAnswer solve(const Maze &maze) override;

private:
	Migite(const Migite &obj);
	const Migite &operator =(const Migite &rhs);

	struct State {
		int x, y;
		enum direction { r, u, l, d } dir;
	};
};
