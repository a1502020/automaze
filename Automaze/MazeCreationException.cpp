#include "MazeCreationException.h"

MazeCreationException::MazeCreationException()
	: std::exception("���H�̍쐬�Ɏ��s���܂����B")
{
}

MazeCreationException::MazeCreationException(const std::string & mes)
	: std::exception(mes.c_str())
{
}
