﻿
# include <Siv3D.hpp>
#include "Maze.h"
#include "Boutaoshi.h"
#include "Michinobashi.h"
#include "Kabenobashi.h"

void Main()
{
	int w = 41, h = 31;

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"迷路自動生成オプション");

	gui.add(GUIText::Create(L"幅"));
	gui.add(L"w", GUISlider::Create(7, 101, w));
	gui.add(GUINewLine::Create());
	gui.add(GUIText::Create(L"高さ"));
	gui.add(L"h", GUISlider::Create(7, 101, h));
	gui.add(GUINewLine::Create());

	gui.add(L"algo", GUIRadioButton::Create({ L"棒倒し法", L"道延ばし法", L"壁延ばし法" }, 0, true));
	std::vector<std::shared_ptr<MazeFactory>> factories = {
		std::make_shared<Boutaoshi>(),
		std::make_shared<Michinobashi>(),
		std::make_shared<Kabenobashi>()
	};
	Maze maze = factories[0]->create(w, h, 1, 1, w - 2, h - 2);

	const ColorF floorCols[] = { {1.0, 1.0, 1.0 }, {0.8, 0.8, 0.8} };
	const ColorF wallCols[] = { {0.2, 0.2, 0.8}, {0.2, 0.2, 0.8} };

	while (System::Update())
	{
		Graphics3D::FreeCamera(1.0);

		// 迷路生成
		if (gui.slider(L"w").hasChanged || gui.slider(L"h").hasChanged || gui.radioButton(L"algo").hasChanged) {
			w = static_cast<int>(gui.slider(L"w").value) / 2 * 2 + 1;
			h = static_cast<int>(gui.slider(L"h").value) / 2 * 2 + 1;
			maze = factories[gui.radioButton(L"algo").checkedItem.value_or(0)]->create(w, h, 1, 1, w - 2, h - 2);
		}

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
