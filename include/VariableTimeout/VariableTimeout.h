#ifndef VARIABLE_TIMEOUT_H
#define VARIABLE_TIMEOUT_H

#include "boost/asio.hpp"
#include <mutex>
#include <thread>

template <class T>
class VariableTimeout
{
public:
	VariableTimeout(int timeout);
	
private:
	int timeout;
	boost::asio::deadline_timer* timer;
	boost::asio::io_service io;
	void invalidate();
	std::thread* ioRunner;

	T variable;
	bool stillValid;
	virtual T obtain() =0;
	std::mutex mtx;

public:
	T getValue();
};

#endif
