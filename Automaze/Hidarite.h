#pragma once

#include "MazeSolver.h"

class Hidarite : public MazeSolver {
public:
	Hidarite();

	MazeAnswer solve(const Maze &maze) override;

private:
	Hidarite(const Hidarite &obj);
	const Hidarite &operator =(const Hidarite &rhs);

	struct State {
		int x, y;
		enum direction { r, u, l, d } dir;
	};
};
