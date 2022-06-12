#include <iostream>
#include "Producer.h"
#include <utility>
Producer::Producer()
{
	m_log = nullptr;
}

void Producer::SetService(Logger& log)
{
	m_log = &log;
	m_log->setCallback(std::bind(&Producer::cb, this, std::placeholders::_1));
}

void Producer::writeLogMes(std::string str)
{
	if (m_log != nullptr)
	{
		m_log->writeLogMes(str);
	}
}

void Producer::cb(int param)
{
	std::cout << "Producer callback: "  <<param<< std::endl;
}