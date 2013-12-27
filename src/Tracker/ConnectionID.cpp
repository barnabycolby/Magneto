#include "Tracker/ConnectionID.h"

#include "Networking/ConnectRequest.h"
#include "Networking/ConnectResponse.h"
#include "Networking/Networking.h"
#include "Tracker/InvalidTracker.h"

#include <vector>
#include "boost/system/system_error.hpp"

#include "Networking/NetworkingTimeout.h"

#include <iostream>
#include <cmath>

using namespace std;

ConnectionID::ConnectionID(URL* trackerURL)
: VariableTimeout(60), trackerURL(trackerURL)
{}

uint64_t ConnectionID::obtain()
{
	// Create the connect request packet
	ConnectRequest connectRequest;

	// Send the structure to the tracker
	vector<unsigned char> response;
	try
	{
		int n;
		// We are supposed to wait until n = 8 and keep trying to connect with n set to 8
		// However this gives a value of 3840 seconds, which is over an hour!!!
		// Normally torrent links come with multiple available trackers, so it makes more
		// sense to simply try another one!
		// n = 2 gives a timeout value of one minute
		for (n = 0; n <= 2; n++)
		{
			int timeout = 15 * pow(2, n);
			try
			{
				response = Networking::syncSendUDPRequest(&connectRequest, this->trackerURL, 15);
				break;
			}
			catch (NetworkingTimeout e)
			{}
		}
		
		// Check whether we were successful or not
		if (n == 3)
		{
			throw NetworkingTimeout();
		}
	}
	catch (boost::system::system_error& e)
	{
		if (e.code().message() == "Host not found (authoritative)")
		{
			throw InvalidTracker("The host could not be found.");
		}
		else
		{
			throw e;
		}
	}

	// Parse the response
	ConnectResponse connectResponse(connectRequest.getTransactionID(), &response);

	return connectResponse.getConnectionID();
}
