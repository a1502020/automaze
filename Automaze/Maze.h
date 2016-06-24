#pragma once

#include <vector>

class Maze {
public:
	Maze(int w, int h);
	Maze(const Maze &obj);

	int width() const;
	int height() const;

	bool &at(int x, int y);
	const bool &at(int x, int y) const;

private:
	const Maze &operator =(const Maze &rhs);

	std::vector<std::vector<char>> cells; // bool ‚Ì“ÁŽê‰»‰ñ”ð‚Å char ‚ðŽg‚Á‚Ä‚¢‚é
};
