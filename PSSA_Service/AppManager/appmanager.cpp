#include "Logger.h "
#include "ILogger.h"
#include "LoggerCon.h"
#include <string>
#include <chrono>
#include "Producer.h"
int AppManager()
{
	Producer prod1;     // producer
	Producer prod2;     // producer
	Logger log;         // service
	LoggerCon m_logCon; // consumer
	LoggerCon m_logSer; // consumer
	prod1.SetService(log);
	prod2.SetService(log);
	log.Subscribe(m_logCon);
	log.Subscribe(m_logSer);

	for (int i = 0; i < 20; i++)
	{
		prod1.writeLogMes("abc");
		prod2.writeLogMes("def");
	}
	std::this_thread::sleep_for(std::chrono::seconds(2));
	log.stop();
	return 0;
}