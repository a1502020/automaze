#include "MazeAnswer.h"

MazeAnswer::MazeAnswer()
{
}

MazeAnswer::MazeAnswer(const MazeAnswer & obj)
	: ps(obj.ps)
{
}

const MazeAnswer & MazeAnswer::operator=(const MazeAnswer & rhs)
{
	ps = rhs.ps;
	return *this;
}

std::size_t MazeAnswer::size() const
{
	return ps.size();
}

MazeAnswer::Pos & MazeAnswer::operator[](std::size_t index)
{
	return ps[index];
}

const MazeAnswer::Pos & MazeAnswer::operator[](std::size_t index) const
{
	return ps[index];
}

void MazeAnswer::add(const Pos & pos)
{
	ps.push_back(pos);
}
