/*
Scenario when no message could be lost and all messages are delivered to all consumers.
After executing the functions below the status of the pointer is:
c1= first non read cell
p = first empty cell
c1 and p can overlap

____________ P_________

|_|_|_|_|_|_|_|_|_|_|_|

	  c1       c2  c3

Multithread:
mutex will be added to protect calling more than once at the same time write or read function.
All the function is critical section, because writing to mem[] and updating flag_c1 must be performed
together to avoid misbehave.

Condvar:
The scenario we need is:
if the c1 catches p, fifo is empty. c1 must wait until p puts something
if the p catches c1, fifo is full. p must wait until c reads something

V1.1
head - points to the first element where we can write. Head is updated by producer.
Tail - not needed, as each element has reference counter.
In each cell a structire payload is written. No other structure is allowed.

struct payload
{
char data; - user data
int refs; - 0<= refs<= consumers; keeps track how many times the cell has been read
}

When producer write to a cell the structure "payload", he updates refs = consumer_count.
When consumer reads a cell, he decrease the count: refs--;
When refs = 0, the cell is read by all consumers and is ready to be written. Head can point to this cell.
When refs !=0, the cell can be read.
Each consumer keeps track on fifo state that is valid for himself only. It helps the consumer to
read more than one cell before waiting on condvar.

*/
#pragma once
#include "ILogger.h"
#include <string>
#include <thread>
#include <mutex>
#include <functional>

enum class fifoStates
{
	empty = 0,
	notempty
};

struct payload
{
    std::string data = "";
	int refs = 0;
};

class Logger
{
public:
	Logger();
	void stop();
	void Subscribe(ILogger &);
	void writeLogMes(std::string);  // producer calls this function
	void sendMesToSubscribers(int); // threads run this function
	void setCallback(std::function<void(int)>);
private:
	static const int maxsubscribers = 10;
	static const int fifosize = 10;
    int subscribers;       // subscribers count
	ILogger *m_log[maxsubscribers];    // all subscribers
	std::thread th[maxsubscribers];    // one thread per subscriber
	int compStatus;        // 0- deinit; 1- init; 2-start; 3- stop
	std::function<void(int)> m_cb; // call back function of producer
	std::mutex fifo_m;
	std::condition_variable cond_p[maxsubscribers];
	std::condition_variable cond_c;
	int c[maxsubscribers] = {0}; // pointers in FIFO
	payload mem[fifosize] = {};
	int head = 0;
	fifoStates fifoState[maxsubscribers]; // fifo can be full for c1 and empty for c2 and partially full for c3
};
