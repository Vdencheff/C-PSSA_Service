#pragma once
//#include "FifoQueue.h"
#include <string>
class ILogger
{
public:
	void virtual writeLogMes(std::string) = 0;
};