#pragma once

#include <vector>

class Maze {
public:
	Maze(int w, int h, int sx, int sy, int gx, int gy);
	Maze(const Maze &obj);

	const Maze &operator =(const Maze &rhs);

	int width() const;
	int height() const;

	int startX() const;
	int startY() const;
	int goalX() const;
	int goalY() const;

	bool &at(int x, int y);
	const bool &at(int x, int y) const;

private:

	std::vector<std::vector<char>> cells; // bool ‚Ì“ÁŽê‰»‰ñ”ð‚Å char ‚ðŽg‚Á‚Ä‚¢‚é
	int sx, sy, gx, gy;
};
