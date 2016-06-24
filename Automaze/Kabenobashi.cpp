#include "Kabenobashi.h"

#include "MazeCreationException.h"
#include <set>

Kabenobashi::Kabenobashi()
{
	std::random_device rnd;
	mt.seed(rnd());
}

Maze Kabenobashi::create(int w, int h, int sx, int sy, int gx, int gy)
{
	if (w % 2 != 1 || h % 2 != 1) {
		throw MazeCreationException("壁延ばし法では、迷路の幅と高さは奇数である必要があります。");
	}
	if (sx % 2 != 1 || sy % 2 != 1 || gx % 2 != 1 || gy % 2 != 1) {
		throw MazeCreationException("壁延ばし法では、スタートとゴールのX・Y座標はそれぞれ奇数である必要があります。");
	}

	Maze temp(w + 4, h + 4, 0, 0, 0, 0);
	for (int x = 0; x < w + 4; ++x) {
		temp.at(x, 0) = true;
		temp.at(x, 2) = true;
		temp.at(x, h + 1) = true;
		temp.at(x, h + 3) = true;
	}
	for (int y = 0; y < h + 4; ++y) {
		temp.at(0, y) = true;
		temp.at(2, y) = true;
		temp.at(w + 1, y) = true;
		temp.at(w + 3, y) = true;
	}
	std::set<std::pair<int, int>> rem;
	for (int x = 4; x < w; x += 2) {
		rem.insert(std::make_pair(x, 2));
		rem.insert(std::make_pair(x, h + 1));
	}
	for (int y = 4; y < h; y += 2) {
		rem.insert(std::make_pair(2, y));
		rem.insert(std::make_pair(w + 1, y));
	}

	while (!rem.empty()) {
		std::uniform_int_distribution<> ud(0, rem.size() - 1);
		auto it = rem.begin();
		for (int i = ud(mt); i > 0; --i) ++it;
		int cx = (*it).first, cy = (*it).second;

		while (true) {
			std::vector<std::pair<int, int>> ps;
			ar4(temp, cx, cy, ps);
			if (ps.size() <= 1) {
				rem.erase(std::make_pair(cx, cy));
				if (ps.empty()) {
					break;
				}
			}
			std::uniform_int_distribution<> ud2(0, ps.size() - 1);
			std::pair<int, int> &p = ps[ud2(mt)];
			int px = p.first, py = p.second;
			temp.at(px, py) = true;
			temp.at((cx + px) / 2, (cy + py) / 2) = true;
			rem.insert(std::make_pair(px, py));
		}
	}

	Maze res(w, h, sx, sy, gx, gy);
	for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
		res.at(x, y) = temp.at(x + 2, y + 2);
	}
	return res;
}

Kabenobashi::Kabenobashi(const Kabenobashi &)
{
}

const Kabenobashi & Kabenobashi::operator=(const Kabenobashi &)
{
	return *this;
}

void Kabenobashi::ar4(const Maze & maze, int x, int y, std::vector<std::pair<int, int>>& out)
{
	if (!maze.at(x + 2, y)) out.push_back(std::make_pair(x + 2, y));
	if (!maze.at(x, y - 2)) out.push_back(std::make_pair(x, y - 2));
	if (!maze.at(x - 2, y)) out.push_back(std::make_pair(x - 2, y));
	if (!maze.at(x, y + 2)) out.push_back(std::make_pair(x, y + 2));
}
