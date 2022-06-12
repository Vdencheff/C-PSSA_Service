#include "LoggerCon.h"
#include <iostream>

LoggerCon::LoggerCon()
{
}

void LoggerCon::writeLogMes(std::string str)
{
	std::cout << "Logger writing: " << str << std::endl;
}