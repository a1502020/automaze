#include "Boutaoshi.h"

#include "MazeCreationException.h"
#include <vector>

Boutaoshi::Boutaoshi()
{
	std::random_device rnd;
	mt.seed(rnd());
}

Maze Boutaoshi::create(int w, int h, int sx, int sy, int gx, int gy)
{
	if (w % 2 != 1 || h % 2 != 1) {
		throw MazeCreationException("棒倒し法では、迷路の幅と高さは奇数である必要があります。");
	}
	if (sx % 2 != 1 || sy % 2 != 1 || gx % 2 != 1 || gy % 2 != 1) {
		throw MazeCreationException("棒倒し法では、スタートとゴールのX・Y座標はそれぞれ奇数である必要があります。");
	}

	Maze res(w, h, sx, sy, gx, gy);

	// 外を壁で埋める
	for (int x = 0; x < w; ++x) {
		res.at(x, 0) = true;
		res.at(x, h - 1) = true;
	}
	for (int y = 0; y < h; ++y) {
		res.at(0, y) = true;
		res.at(w - 1, y) = true;
	}

	// 棒倒し
	for (int x = 2; x < w - 2; x += 2) for (int y = 2; y < h - 2; y += 2) {
		res.at(x, y) = true;

		std::vector<std::pair<int, int>> ps;
		if (y == 2) ps.push_back(std::make_pair(x, y - 1));
		if (!res.at(x + 1, y)) ps.push_back(std::make_pair(x + 1, y));
		if (!res.at(x - 1, y)) ps.push_back(std::make_pair(x - 1, y));
		if (!res.at(x, y + 1)) ps.push_back(std::make_pair(x, y + 1));
		std::uniform_int_distribution<> rd(0, ps.size() - 1);
		int p = rd(mt);
		res.at(ps[p].first, ps[p].second) = true;
	}

	return res;
}

Boutaoshi::Boutaoshi(const Boutaoshi &)
{
}

const Boutaoshi & Boutaoshi::operator=(const Boutaoshi &)
{
	return *this;
}
