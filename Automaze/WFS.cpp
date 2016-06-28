#include "WFS.h"

#include <queue>

WFS::WFS()
{
}

MazeAnswer WFS::solve(const Maze & maze)
{
	const int sx = maze.startX(), sy = maze.startY();
	const int gx = maze.goalX(), gy = maze.goalY();
	const int w = maze.width(), h = maze.height();

	State first;
	first.ans.add({ sx,sy });
	first.vted.assign(w, std::vector<bool>(h, false));

	std::queue<State> q;
	q.push(first);

	MazeAnswer ans;
	bool done = false;

	while (!q.empty() && !done) {
		State s = q.front(); q.pop();
		const MazeAnswer::Pos p = s.ans[s.ans.size() - 1];
		s.vted[p.x][p.y] = true;
		for (int i = 0; i < 4; ++i) {
			const int x = p.x + ar4[i][0], y = p.y + ar4[i][1];
			if (!maze.at(x, y) && !s.vted[x][y]) {
				State s2 = s;
				s2.ans.add({ x, y });
				if (x == gx && y == gy) {
					ans = s2.ans;
					done = true;
					break;
				}
				q.push(s2);
			}
		}
	}

	return ans;
}

WFS::WFS(const WFS &)
{
}

const WFS & WFS::operator=(const WFS &)
{
	return *this;
}

const int WFS::ar4[4][2] = {
	{ 1, 0 }, { 0, -1 }, { -1, 0 }, { 0, 1 }
};
