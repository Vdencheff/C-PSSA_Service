#pragma once
#include "ILogger.h"
#include "FifoQueue.h"
#include <string>

class LoggerCon : public ILogger
{
public:
	LoggerCon();
	void writeLogMes(std::string) override;
};
