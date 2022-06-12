#pragma once
//#include "FifoQueue.h"
#include "Logger.h "
#include <string>
#include <functional>

class Producer 
{
public:
	Producer();
	void SetService(Logger &log);
	void writeLogMes(std::string str);

private:
	void cb(int); // callback
	Logger* m_log{nullptr}; // service
};
