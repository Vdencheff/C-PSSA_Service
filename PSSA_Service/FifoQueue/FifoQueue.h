#pragma once
#include <string>

struct Queue
{
	std::string str;
	// from 0 to num subscribers. Each subscriber when reads the message will decrease this value
	// producer when produce entry, will make this value equal to number of subscribers
	int isFull;
};

class FifoQueue
{
public:
	Queue buffer[20];

};