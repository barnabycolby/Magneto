#include "Tracker/InvalidTracker.h"

InvalidTracker::InvalidTracker(string message) : message(message) {}
InvalidTracker::~InvalidTracker() throw() {}

const char* InvalidTracker::what() throw()
{
	return ("Tracker was invalid: " + this->message).c_str();
}
