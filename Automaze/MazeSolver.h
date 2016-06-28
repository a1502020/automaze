#pragma once

#include "Maze.h"
#include "MazeAnswer.h"

class MazeSolver {
public:
	virtual ~MazeSolver();

	virtual MazeAnswer solve(const Maze &maze) = 0;
};
