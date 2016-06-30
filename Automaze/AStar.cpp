#include "AStar.h"

#include <queue>
#include <vector>
#include <functional>
#include <cmath>
#include <list>

#define h(x, y) (std::abs(gx - (x)) + std::abs(gy - (y)))

using P = std::pair<int, std::pair<int, int>>;

AStar::AStar()
{
}

MazeAnswer AStar::solve(const Maze & maze)
{
	const int w = maze.width(), h = maze.height();
	const int sx = maze.startX(), sy = maze.startY();
	const int gx = maze.goalX(), gy = maze.goalY();

	std::vector<std::vector<bool>> vted(w, std::vector<bool>(h, false));
	std::vector<std::vector<std::pair<int, int>>> parent(w, std::vector<std::pair<int, int>>(h, std::make_pair(-1, -1)));

	std::priority_queue<P, std::vector<P>, std::greater<P>> q;
	q.push(std::make_pair(h(sx, sy), std::make_pair(sx, sy)));

	while (!q.empty()) {
		P p = q.top(); q.pop();
		const int f = p.first, x = p.second.first, y = p.second.second;
		vted[x][y] = true;
		if (x == gx && y == gy) break;
		for (int i = 0; i < 4; ++i) {
			const int arx = x + ar4[i][0], ary = y + ar4[i][1];
			if (maze.at(arx, ary)) continue;
			if (!vted[arx][ary]) {
				const int arf = f - h(x, y) + h(arx, ary);
				parent[arx][ary] = std::make_pair(x, y);
				q.push(std::make_pair(arf, std::make_pair(arx, ary)));
			}
		}
	}

	if (parent[gx][gy].first == -1) {
		return MazeAnswer();
	}
	else {
		std::list<std::pair<int, int>> res;
		int x = gx, y = gy;
		res.push_front(std::make_pair(x, y));
		while (x != sx || y != sy) {
			std::pair<int, int> p = parent[x][y];
			x = p.first;
			y = p.second;
			res.push_front(std::make_pair(x, y));
		}
		MazeAnswer ans;
		for (const auto &p : res) {
			ans.add({ p.first, p.second });
		}
		return ans;
	}
}

AStar::AStar(const AStar &)
{
}

const AStar & AStar::operator=(const AStar &)
{
	return *this;
}

const int AStar::ar4[4][2] = {
	{ 1, 0 }, { 0, -1 }, { -1, 0 }, { 0, 1 }
};