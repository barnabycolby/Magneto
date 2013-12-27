#include "Networking/ConnectResponse.h"

#include "Networking/InvalidUDPResponse.h"

#include <iostream>

ConnectResponse::ConnectResponse(uint32_t transaction_id, vector<unsigned char>* response)
: UDPResponse(response)
{
	// Packet should be at least 16 bytes
	if (response->size() < 16)
	{
		throw InvalidUDPResponse("Packet length was too small.");
	}

	// Parse the data
	this->action         = this->get32BitInt();
	this->transaction_id = this->get32BitInt();
	this->connection_id  = this->get64BitInt();

	// The transaction_id should be equal to the one we chose
	if (this->transaction_id != transaction_id)
	{
		throw InvalidUDPResponse("Transaction ID was invalid.");
	}

	// Check whether the action is connect
	if (this->action != 0)
	{
		throw InvalidUDPResponse("Action was invalid.");
	}
}

uint64_t ConnectResponse::getConnectionID()
{
	return this->connection_id;
}
