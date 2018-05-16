#pragma once

#include <string>
#include <vector>

#define PARENT(i) ((i + 1) / 2 - 1)
#define LEFT(i) (2 * (i + 1) - 1)
#define RIGHT(i) (2 * (i + 1))

struct Element
{
	unsigned int val;
	unsigned int parent;
	double d;

	Element() : val{ 0 }, parent{ 0 }, d{ std::numeric_limits<double>::max() } {}
	Element(unsigned int val, unsigned int parent, double d) : val{ val }, parent{ parent }, d{ d } {}
};

class PriorityQueue
{
private:
	std::vector<std::shared_ptr<Element>> queue;
	unsigned int heap_size;

	bool find_next(unsigned int start, int x, unsigned int &i);
	void heapify(unsigned int i);
	void inner_priority(unsigned int i, double d);

public:
	PriorityQueue();
	~PriorityQueue();

	void insert(int x, unsigned int parent, double p);
	bool empty();
	unsigned int top();
	unsigned int pop();
	void priority(unsigned int x, double d);
	bool in_queue(unsigned int x);
	bool in_queue(unsigned int x, unsigned int &i);
	std::shared_ptr<Element> at(unsigned int i);
	std::vector<std::shared_ptr<Element>> get_data();
	std::string to_string();
};

