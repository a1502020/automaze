
# include <Siv3D.hpp>
#include "Maze.h"
#include "Boutaoshi.h"
#include "Michinobashi.h"
#include "Kabenobashi.h"
#include "MazeSolver.h"
#include "DummySolver.h"
#include "Migite.h"
#include "WFS.h"

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

	GUI gui2(GUIStyle::Default);
	gui2.setTitle(L"迷路ソルバーオプション");

	gui2.add(L"algo", GUIRadioButton::Create({ L"なし", L"右手法", L"WFS(幅優先探索)" }, 0));
	std::vector<std::shared_ptr<MazeSolver>> solvers = {
		std::make_shared<DummySolver>(),
		std::make_shared<Migite>(),
		std::make_shared<WFS>()
	};
	MazeAnswer ans;
	std::vector<std::vector<int>> ansArr(w, std::vector<int>(h, 0));
	int anim = 0;

	const ColorF floorCols[] = { {1.0, 1.0, 1.0 }, {0.8, 0.8, 0.8} };
	const ColorF ansCols[] = { {1.0, 0.5, 0.0}, {0.8, 0.4, 0.0} };
	const ColorF wallCols[] = { {0.2, 0.2, 0.8}, {0.2, 0.2, 0.8} };

	while (System::Update())
	{
		Graphics3D::FreeCamera(1.0);

		// 迷路生成
		if (gui.slider(L"w").hasChanged || gui.slider(L"h").hasChanged || gui.radioButton(L"algo").hasChanged) {
			w = static_cast<int>(gui.slider(L"w").value) / 2 * 2 + 1;
			h = static_cast<int>(gui.slider(L"h").value) / 2 * 2 + 1;
			maze = factories[gui.radioButton(L"algo").checkedItem.value_or(0)]->create(w, h, 1, 1, w - 2, h - 2);
			ansArr.assign(w, std::vector<int>(h, 0));
			anim = 0;
		}

		// 迷路を解く
		if (gui2.radioButton(L"algo").hasChanged) {
			ans = solvers[gui2.radioButton(L"algo").checkedItem.value_or(0)]->solve(maze);
			ansArr.assign(w, std::vector<int>(h, 0));
			for (int i = 0; i < ans.size(); ++i) {
				if (ansArr[ans[i].x][ans[i].y] == 0) {
					ansArr[ans[i].x][ans[i].y] = i + 1;
				}
			}
			anim = 0;
		}

		// 回答のアニメーション
		++anim;
		if (anim > ans.size() + 60) anim = 0;

		for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
			if (maze.at(x, y)) {
				// 壁
				Box(Vec3(x, 0, h - y), 1).draw(wallCols[(x + y) % 2]);
			}
			else {
				// 床
				if (ansArr[x][y] != 0 && ansArr[x][y] <= anim) {
					Plane(Vec3(x, 0, h - y), 1).draw(ansCols[(x + y) % 2]);
				}
				else {
					Plane(Vec3(x, 0, h - y), 1).draw(floorCols[(x + y) % 2]);
				}
			}
		}
	}
}
