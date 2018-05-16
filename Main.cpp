#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "PriorityQueue.h"

struct Edge
{
	unsigned int in, out;
	double w;

	Edge() : in{ 0 }, out{ 0 }, w{ -1 } {}
	Edge(unsigned int in, unsigned int out, double w) : in{ in }, out{ out }, w{ w } {}
};

std::vector<Element> Djikstra(unsigned int max_vec, unsigned int start, std::vector<Edge> edges)
{
	std::vector<Element> S;

	PriorityQueue pq;
	for (unsigned int i = 1; i <= max_vec; i++)
	{
		pq.insert(i, 0, (i == start) ? 0.0 : std::numeric_limits<double>::max());
	}

	std::vector<std::list<std::pair<unsigned int, double>>> adj(max_vec + 1);
	for (unsigned int i = 0; i < edges.size(); i++)
	{
		adj[edges[i].in].push_back(std::pair<unsigned int, double>(edges[i].out, edges[i].w));
	}

	while (!pq.empty())
	{
		double ud = pq.at(0)->d;
		S.push_back(*pq.at(0));
		unsigned int u = pq.pop();

		for (auto v : adj[u])
		{
			unsigned int i;
			pq.in_queue(v.first, i);

			if (pq.at(i)->d > ud + v.second)
			{
				pq.at(i)->parent = u;
				pq.priority(v.first, ud + v.second);
			}
		}
	}

	return S;
}

int main(int argc, char* argv[])
{
	unsigned int n, m;
	std::cin >> n >> m;

	unsigned int u, v, s;
	double w;

	std::vector<Edge> edges(m);
	for (unsigned int i = 0; i < m; i++)
	{
		std::cin >> u >> v >> w;
		edges[i] = Edge(u, v, w);
	}
	std::cin >> s;

	std::vector<Element> paths = Djikstra(n, s, edges);
	std::sort(paths.begin(), paths.end(), [=](Element a, Element b) { return a.val < b.val; });
	for (unsigned int i = 0; i < paths.size(); i++)
	{
		std::cout << paths[i].val << " " << paths[i].d << std::endl;

		Element current = paths[i];
		std::list<Element> path;
		while (current.val != s)
		{
			path.push_front(current);
			current = paths[paths[current.val - 1].parent - 1];
		}

		double diff = 0;
		std::cerr << s << " ";
		for (auto j = path.begin(); j != path.end(); j++)
		{
			std::cerr << "-[w=" << (j->d - diff) << "]-> " << j->val << " ";
			diff += j->d - diff;
		}
		std::cerr << std::endl;
	}

	return 0;
}