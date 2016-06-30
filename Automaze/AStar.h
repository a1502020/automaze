#pragma once

#include "MazeSolver.h"

class AStar : public MazeSolver {
public:
	AStar();

	MazeAnswer solve(const Maze &maze);

private:
	AStar(const AStar &obj);
	const AStar &operator =(const AStar &rhs);

	static const int ar4[4][2];
};
