
# include <Siv3D.hpp>
#include "Maze.h"
#include "Boutaoshi.h"
#include "Michinobashi.h"

void Main()
{
	const int w = 41, h = 31;
	//Boutaoshi boutaoshi;
	//Maze maze = boutaoshi.create(w, h, 1, 1, w - 2, h - 2);
	Michinobashi michi;
	Maze maze = michi.create(w, h, 1, 1, w - 2, h - 2);

	const ColorF floorCols[] = { {1.0, 1.0, 1.0 }, {0.8, 0.8, 0.8} };
	const ColorF wallCols[] = { {0.2, 0.2, 0.8}, {0.2, 0.2, 0.8} };

	while (System::Update())
	{
		Graphics3D::FreeCamera(1.0);

		for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
			if (maze.at(x, y)) {
				// 壁
				Box(Vec3(x, 0, y), 1).draw(wallCols[(x + y) % 2]);
			}
			else {
				// 床
				Plane(Vec3(x, 0, y), 1).draw(floorCols[(x + y) % 2]);
			}
		}
	}
}
