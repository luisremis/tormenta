#ifndef _Spout_H_
#define _Spout_H_

#include <thread>
#include <string>
#include <vector>
#include <list>
#include <mutex>

#include "crane_types.h"
#include "Tuple.h"
#include "Bolt.h"

class Spout
{

protected: 

	std::string name; 

	uint32_t spoutId;
	uint32_t parallel_level;

	std::vector<struct BoltSubscriptor> subscriptors;

	std::vector<std::string> subscriptorsAdd;
	std::vector<uint32_t> subscriptorsPort;

	std::mutex tupleQueueLock;
	std::list<Tuple> tupleQueue;

	std::thread generate;
	bool killGenerateThread;

	std::thread communication;
	bool killCommunicationThread;

	virtual void communicationThread();
	virtual void generateTuples();

	void emit(Tuple& tuple);

public: 

	Spout(std::string, unsigned int parallel_level);
	virtual ~Spout();

	virtual void run();
	virtual void stop();

	void subscribe(Bolt& bolt);

	uint32_t getSpoutId();
	uint32_t getParallelLevel();
	std::string getName();

};

#endif