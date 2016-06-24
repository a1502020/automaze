#pragma once

#include "MazeFactory.h"
#include <random>

class Boutaoshi : public MazeFactory {
public:
	Boutaoshi();

	Maze create(int w, int h, int sx, int sy, int gx, int gy) override;

private:
	Boutaoshi(const Boutaoshi &obj);
	const Boutaoshi &operator =(const Boutaoshi &rhs);

	std::mt19937 mt;
};
