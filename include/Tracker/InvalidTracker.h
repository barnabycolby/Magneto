#ifndef INVALID_TRACKER_H
#define INVALID_TRACKER_H

#include <exception>
#include <string>

using namespace std;

class InvalidTracker: public exception
{
public:
	InvalidTracker(string message);
	~InvalidTracker() throw();

	virtual const char* what() throw();

private:
	string message;
};

#endif
