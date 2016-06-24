#include "MazeCreationException.h"

MazeCreationException::MazeCreationException()
	: std::exception("ñ¿òHÇÃçÏê¨Ç…é∏îsÇµÇ‹ÇµÇΩÅB")
{
}

MazeCreationException::MazeCreationException(const std::string & mes)
	: std::exception(mes.c_str())
{
}
