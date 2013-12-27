#ifndef NETWORKING_TIMEOUT_H
#define NETWORKING_TIMEOUT_H

#include <exception>
#include <string>

using namespace std;

class NetworkingTimeout: public exception
{
public:
	const char* what() throw()
	{
		return "The networking request timed out.";
	}
};

#endif
