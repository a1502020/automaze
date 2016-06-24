#pragma once

#include "MazeFactory.h"
#include <random>

class Kabenobashi : public MazeFactory {
public:
	Kabenobashi();

	Maze create(int w, int h, int sx, int sy, int gx, int gy) override;

private:
	Kabenobashi(const Kabenobashi &obj);
	const Kabenobashi &operator =(const Kabenobashi &rhs);

	std::mt19937 mt;

	void ar4(const Maze &maze, int x, int y, std::vector<std::pair<int, int>> &out);
};
