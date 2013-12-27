#include "VariableTimeout/VariableTimeout.h"

#include "boost/date_time/posix_time/posix_time.hpp"
#include <cstdint>
#include "boost/bind.hpp"

#include <iostream>

template <class T>
VariableTimeout<T>::VariableTimeout(int timeout)
: timeout(timeout), stillValid(false)
{
	this->timer = new boost::asio::deadline_timer(this->io, boost::posix_time::seconds(this->timeout));
}

template <class T>
T VariableTimeout<T>::getValue()
{
	this->mtx.lock();
	bool localStillValid = this->stillValid;
	this->mtx.unlock();

	if (!localStillValid)
	{
		// Get the new variable value
		this->variable = this->obtain();

		// Let everyone know that it's valid
		this->mtx.lock();
		this->stillValid = true;
		this->mtx.unlock();

		// Reset the timer
		this->timer->expires_from_now(boost::posix_time::seconds(this->timeout));
		this->timer->async_wait(boost::bind(&VariableTimeout::invalidate, this));
		this->io.reset();
		this->ioRunner = new std::thread(boost::bind(&boost::asio::io_service::run, &io));
	}

	return this->variable;
}

template <class T>
void VariableTimeout<T>::invalidate()
{
	this->mtx.lock();
	this->stillValid = false;
	this->mtx.unlock();
}

template class VariableTimeout<uint64_t>;
