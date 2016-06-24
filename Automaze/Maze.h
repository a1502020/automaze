#pragma once

#include <vector>

class Maze {
public:
	Maze(int w, int h, int sx, int sy, int gx, int gy);
	Maze(const Maze &obj);

	int width() const;
	int height() const;

	int startX() const;
	int startY() const;
	int goalX() const;
	int goalY() const;

	bool &at(int x, int y);
	const bool &at(int x, int y) const;

private:
	const Maze &operator =(const Maze &rhs);

	std::vector<std::vector<char>> cells; // bool �̓��ꉻ����� char ���g���Ă���
	int sx, sy, gx, gy;
};
