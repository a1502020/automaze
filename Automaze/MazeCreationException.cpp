#include "MazeCreationException.h"

MazeCreationException::MazeCreationException()
	: std::exception("迷路の作成に失敗しました。")
{
}

MazeCreationException::MazeCreationException(const std::string & mes)
	: std::exception(mes.c_str())
{
}
