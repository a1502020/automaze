#pragma once

#include <exception>
#include <string>

class MazeCreationException : public std::exception {
public:
	MazeCreationException();
	MazeCreationException(const std::string &mes);
};