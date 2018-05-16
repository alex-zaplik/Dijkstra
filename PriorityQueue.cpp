#include "PriorityQueue.h"

#include <sstream>

PriorityQueue::PriorityQueue()
{
	heap_size = 0;
}

PriorityQueue::~PriorityQueue()
{
}

bool PriorityQueue::find_next(unsigned int start, int x, unsigned int &i)
{
	for (i = start; i < heap_size; i++)
	{
		if (queue[i].val == x)
		{
			return true;
		}
	}

	return false;
}

void PriorityQueue::heapify(unsigned int i)
{
	unsigned int l = LEFT(i);
	unsigned int r = RIGHT(i);
	unsigned int largest;

	if (l < heap_size && queue[l].d < queue[i].d)
	{
		largest = l;
	}
	else
	{
		largest = i;
	}

	if (r < heap_size && queue[r].d < queue[largest].d)
	{
		largest = r;
	}

	if (largest != i)
	{
		std::swap(queue[i], queue[largest]);
		heapify(largest);
	}
}

void PriorityQueue::insert(int x, unsigned int parent, double d)
{
	Element e(x, parent, std::numeric_limits<double>::max());
	heap_size++;

	if (heap_size > queue.size())
	{
		queue.resize(heap_size);
	}
	queue[heap_size - 1] = e;

	inner_priority(heap_size - 1, d);
}

bool PriorityQueue::empty()
{
	return heap_size == 0;
}

unsigned int PriorityQueue::top()
{
	return queue[0].val;
}

unsigned int PriorityQueue::pop()
{
	if (heap_size < 1)
	{
		return 0;
	}

	Element max = queue[0];
	queue[0] = queue[heap_size - 1];
	heap_size--;
	heapify(0);

	return max.val;
}

void PriorityQueue::inner_priority(unsigned int i, double d)
{
	if (d > queue[i].d)
	{
		return;
	}

	queue[i].d = d;
	while (i > 0 && queue[PARENT(i)].d > queue[i].d)
	{
		std::swap(queue[i], queue[PARENT(i)]);
		i = PARENT(i);
	}
}

void PriorityQueue::priority(unsigned int x, double d)
{
	unsigned int i = 0;
	while (find_next(i, x, i))
	{
		Element before = queue[i];
		inner_priority(i, d);
		if (queue[i].val == before.val && queue[i].d == before.d) i++;
	}
}

bool PriorityQueue::in_queue(unsigned int x)
{
	unsigned int i;
	return find_next(0, x, i);
}

bool PriorityQueue::in_queue(unsigned int x, unsigned int &i)
{
	return find_next(0, x, i);
}

Element* PriorityQueue::at(unsigned int i)
{
	return &queue[i];
}

std::vector<Element> PriorityQueue::get_data()
{
	return std::vector<Element>(queue.begin(), queue.begin() + heap_size - 1);
}

std::string PriorityQueue::to_string()
{
	std::stringstream ss;

	for (unsigned int i = 0; i < heap_size; i++)
	{
		ss << "(" << queue[i].val << ", " << queue[i].d << ") ";
	}

	return ss.str();
}
