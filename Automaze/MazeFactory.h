#pragma once

#include "Maze.h"

class MazeFactory {
public:
	virtual ~MazeFactory();

	virtual Maze create(int w, int h, int sx, int sy, int gx, int gy) = 0;
};
