
# include <Siv3D.hpp>
#include "Maze.h"

void Main()
{
	Maze maze(41, 31);
	const int w = maze.width(), h = maze.height();

	for (int x = 0; x < w; ++x) {
		maze.at(x, 0) = true;
		maze.at(x, h - 1) = true;
	}
	for (int y = 0; y < h; ++y) {
		maze.at(0, y) = true;
		maze.at(w - 1, y) = true;
	}

	const ColorF cols[] = { {1.0, 1.0, 1.0 }, {0.8, 0.8, 0.8} };

	while (System::Update())
	{
		Graphics3D::FreeCamera(1.0);

		for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
			if (maze.at(x, y)) {
				// 壁
				Box(Vec3(x, 0, y), 1).draw(cols[(x + y) % 2]);
			}
			else {
				// 床
				Plane(Vec3(x, 0, y), 1).draw(cols[(x + y) % 2]);
			}
		}
	}
}
