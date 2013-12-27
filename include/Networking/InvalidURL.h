#ifndef INVALID_URL_H
#define INVALID_URL_H

#include <exception>
#include <string>

using namespace std;

class InvalidURL : public exception
{
public:
	InvalidURL(string message);
	~InvalidURL() throw();

	virtual const char* what() throw();

private:
	string message;
};

#endif
