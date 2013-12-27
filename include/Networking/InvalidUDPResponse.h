#ifndef INVALID_UDP_RESPONSE_H
#define INVALID_UDP_RESPONSE_H

#include <exception>
#include <string>

using namespace std;

class InvalidUDPResponse : public exception
{
public:
	InvalidUDPResponse(string message);
	~InvalidUDPResponse() throw();

	virtual const char* what() throw();

private:
	string message;	
};

#endif
