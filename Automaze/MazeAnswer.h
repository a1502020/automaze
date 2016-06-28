#pragma once

#include <vector>

class MazeAnswer {
public:
	struct Pos {
		int x, y;
		Pos() : x(0), y(0) {}
		Pos(int x, int y) : x(x), y(y) {}
	};

	MazeAnswer();
	const MazeAnswer(const MazeAnswer &obj);

	const MazeAnswer &operator =(const MazeAnswer &rhs);

	std::size_t size() const;

	Pos &operator[](std::size_t index);
	const Pos &operator[](std::size_t index) const;

	void add(const Pos &pos);

private:
	std::vector<Pos> ps;
};
