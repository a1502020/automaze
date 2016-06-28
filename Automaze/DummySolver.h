#pragma once

#include "MazeSolver.h"

class DummySolver : public MazeSolver {
public:
	MazeAnswer solve(const Maze &maze);
};