#ifndef NETWORKING_H
#define NETWORKING_H

#include "Networking/UDPRequest.h"

#include "Tracker/Tracker.h"

#include <vector>
#include <cstdint>

class Networking
{
public:
	static vector<unsigned char> syncSendUDPRequest(UDPRequest* request, URL* url, int timeout);

private:
	static vector<unsigned char> returnValue;

private:
	// Successful operation
	static void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);

	// Timeout
	static void handle_timeout(const boost::system::error_code& error);
};

#endif
