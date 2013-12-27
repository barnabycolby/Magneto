#include "Networking/InvalidURL.h"

#include <string>

using namespace std;

InvalidURL::InvalidURL(string message) : message(message) {}
InvalidURL::~InvalidURL() throw() {}

const char* InvalidURL::what() throw()
{
	return ("URL was invalid: " + this->message).c_str();
}
