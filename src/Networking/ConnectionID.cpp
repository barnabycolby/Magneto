#include "Tracker/ConnectionID.h"

#include "Networking/ConnectRequest.h"
#include "Networking/ConnectResponse.h"
#include "Networking/Networking.h"

#include <vector>
#include "boost/system/system_error.hpp"

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
		response = Magneto::syncSendUDPRequest(&connectRequest, this->trackerURL);
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
