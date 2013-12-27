#include "Networking/InvalidUDPResponse.h"

InvalidUDPResponse::InvalidUDPResponse(string message) : message(message) {}
InvalidUDPResponse::~InvalidUDPResponse() throw() {}

const char* InvalidUDPResponse::what() throw()
{
	return ("UDP Response was invalid: " + this->message).c_str();
}
