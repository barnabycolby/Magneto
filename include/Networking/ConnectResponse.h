#ifndef CONNECT_RESPONSE_H
#define CONNECT_RESPONSE_H

#include "Networking/UDPResponse.h"

class ConnectResponse : public UDPResponse
{
public:
	// Constructor
	ConnectResponse(uint32_t transaction_id, vector<unsigned char>* response);

private:
	uint32_t action;
	uint32_t transaction_id;
	uint64_t connection_id;

public:
	uint64_t getConnectionID();
};

#endif
