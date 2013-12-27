#include "Networking/ConnectRequest.h"

#include <iostream>

// Constructor
ConnectRequest::ConnectRequest()
{
	// Generate the data
	uint64_t connection_id = 0x41727101980;
	uint32_t action = 0;

	// Add the data to the request
	this->add64BitInt(connection_id);
	this->add32BitInt(action);
	this->add32BitInt(this->transaction_id);
}
