#include "Michinobashi.h"

#include "MazeCreationException.h"
#include <set>

Michinobashi::Michinobashi()
{
	std::random_device rnd;
	mt.seed(rnd());
}

Maze Michinobashi::create(int w, int h, int sx, int sy, int gx, int gy)
{
	if (w % 2 != 1 || h % 2 != 1) {
		throw MazeCreationException("道延ばし法では、迷路の幅と高さは奇数である必要があります。");
	}
	if (sx % 2 != 1 || sy % 2 != 1 || gx % 2 != 1 || gy % 2 != 1) {
		throw MazeCreationException("道延ばし法では、スタートとゴールのX・Y座標はそれぞれ奇数である必要があります。");
	}

	Maze temp(w + 2, h + 2, 0, 0, 0, 0);
	for (int y = 1; y < h + 1; ++y) for (int x = 1; x < w + 1; ++x) {
		temp.at(x, y) = true;
	}
	std::set<std::pair<int, int>> rem;
	std::uniform_int_distribution<> udx(0, w / 2 - 1), udy(0, h / 2 - 1);
	int fx = udx(mt) * 2 + 2, fy = udy(mt) * 2 + 2;
	rem.insert(std::make_pair(fx, fy));
	temp.at(fx, fy) = false;

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
			temp.at(px, py) = false;
			temp.at((cx + px) / 2, (cy + py) / 2) = false;
			rem.insert(std::make_pair(px, py));
		}
	}

	Maze res(w, h, sx, sy, gx, gy);
	for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
		res.at(x, y) = temp.at(x + 1, y + 1);
	}
	return res;
}

Michinobashi::Michinobashi(const Michinobashi &)
{
}

const Michinobashi & Michinobashi::operator=(const Michinobashi &)
{
	return *this;
}

void Michinobashi::ar4(const Maze & maze, int x, int y, std::vector<std::pair<int, int>>& out)
{
	if (maze.at(x + 2, y)) out.push_back(std::make_pair(x + 2, y));
	if (maze.at(x, y - 2)) out.push_back(std::make_pair(x, y - 2));
	if (maze.at(x - 2, y)) out.push_back(std::make_pair(x - 2, y));
	if (maze.at(x, y + 2)) out.push_back(std::make_pair(x, y + 2));
}
