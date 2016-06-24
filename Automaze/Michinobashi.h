#pragma once

#include "MazeFactory.h"
#include <random>

class Michinobashi : public MazeFactory {
public:
	Michinobashi();

	Maze create(int w, int h, int sx, int sy, int gx, int gy) override;

private:
	Michinobashi(const Michinobashi &obj);
	const Michinobashi &operator =(const Michinobashi &rhs);

	std::mt19937 mt;

	void ar4(const Maze &maze, int x, int y, std::vector<std::pair<int, int>> &out);
};
