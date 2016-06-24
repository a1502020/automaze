#include "Maze.h"

Maze::Maze(int w, int h)
	: cells(w, std::vector<char>(h, false))
{
}

Maze::Maze(const Maze & obj)
	: cells(obj.cells)
{
}

int Maze::width() const
{
	return cells.size();
}

int Maze::height() const
{
	return (cells.size() == 0) ? 0 : cells[0].size();
}

bool & Maze::at(int x, int y)
{
	return *reinterpret_cast<bool *>(&cells[x][y]);
}

const bool & Maze::at(int x, int y) const
{
	return *reinterpret_cast<const bool *>(&cells[x][y]);
}

const Maze & Maze::operator=(const Maze & rhs)
{
	return *this;
}
