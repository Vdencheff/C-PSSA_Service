#include "Logger.h"
#include <iostream>

Logger::Logger()
{
	for (int i = 0; i < maxsubscribers; i++)
	{
		m_log[i] = nullptr;
		fifoState[i] = fifoStates::empty;
	}
	compStatus = 0;
	subscribers = 0;
}

// producer subscribes for service
void Logger::Subscribe(ILogger& log)
{
	compStatus = 2;
	m_log[subscribers] = &log; // this will be used if each producer has own call back function. logger must have array of producer callbacks
	if (subscribers < maxsubscribers)
	{
		th[subscribers] = std::thread(&Logger::sendMesToSubscribers, this, subscribers);
		subscribers++;
	}
}

void Logger::stop()
{
	compStatus = 3;

	for(int i = 0; i < subscribers; i++)
	{
		cond_p[i].notify_one(); // if any consumer is waiting on condvar wake him up. he will see that stop is requested.
		if (th[i].joinable())
		{
			th[i].join();
		}
	}
}

// producer calls this function to send message to the service
void Logger::writeLogMes(std::string str)
{
	std::unique_lock<std::mutex> ul(fifo_m);
	// stops, check that the point we have pointed is with 0 refs so we can write there
	cond_c.wait(ul, [&] {return mem[head].refs == 0; }); // wait if refs are different from 0. continue if refs are = 0
	// if we are here it means there is a free space in fifo, we can insert at least one element
	mem[head].data = str;
	mem[head].refs = subscribers; // update the refs to the number of consumers. Each consumer when read this cell will decrease the value by 1.
	std::cout << "write mem[" << head << "]: data= " << mem[head].data << "; refs = " << mem[head].refs << std::endl;

	if (head == fifosize - 1) { head = 0; std::cout << "Producer moves write pointer to the begining" << std::endl; }
	else { head++; }

	// after inserting one element, check the fifo state for all consumers, it could be full for some of them
	for (int e = 0; e < subscribers; e++)
	{
		if (fifoState[e] == fifoStates::empty) // notify the consumer not to wait on condvar only if it has been waiting
			cond_p[e].notify_one();

		fifoState[e] = fifoStates::notempty;   // having inserted an element, no consumer can be empty
	}
}

// thread calls this function to send messages to subscribers
// callback at the end has test purposes. No meaning in multiple producer mulitple conusmer case.
// In real application the callback is used to notify the producer that the message has been delivered to the conumer
// In our case the producer does not say which is the consumer or that he is the producer of the message, so the conusmer does not know who to notify.
 void Logger::sendMesToSubscribers(int consumer)
{
	while (compStatus == 2) // thread is allive while comp is started
	{

		std::unique_lock<std::mutex> ul(fifo_m);

		cond_p[consumer].wait(ul, [&] {return fifoState[consumer] != fifoStates::empty || compStatus == 3; }); // wait if fifo is empty
		if (compStatus == 3) return;
		// if we are here it means there is at least one element in fifo, we can read at least one element
		std::cout << "Consumer" << consumer << " reads mem[" << c[consumer] << "]: data= " << mem[c[consumer]].data << " refs = " << mem[c[consumer]].refs << std::endl;

		mem[c[consumer]].refs--; // update the read cell
		// update consumer pointer
		if (c[consumer] == fifosize - 1) { c[consumer] = 0; std::cout << "Consumer" << consumer << "  moves read pointer to the begining" << std::endl; }
		else { c[consumer]++; }

		// the producer will be signalled by each consumer that finds empty cell
		if (mem[head].refs == 0) // the producer will be modified only if there is empty element at head position (there could be more empty elemets)
			cond_c.notify_one();
		if (c[consumer] == head)               // c catch up p, fifo is empty for this consumer
			fifoState[consumer] = fifoStates::empty;
		else
			fifoState[consumer] = fifoStates::notempty;
		m_cb(3); // call producer callback. If m_cb is an array, then call the corresponding callback
	}
}

void Logger::setCallback(std::function<void(int)>cb)
{
	// only the last procucer call back will be registered, not ok for real application
	m_cb =  cb; // each producer has own callback, then m_cb must be array - keeps ref to each producer callback
}
