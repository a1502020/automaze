#pragma once

#include "MazeSolver.h"

class WFS : public MazeSolver {
public:
	WFS();

	MazeAnswer solve(const Maze &maze);

private:
	WFS(const WFS &obj);
	const WFS &operator =(const WFS &rhs);

	struct State {
		MazeAnswer ans;
		std::vector<std::vector<bool>> vted;
	};
	static const int ar4[4][2];
};