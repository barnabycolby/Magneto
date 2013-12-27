#include "Tracker/Tracker.h"

#include "Tracker/InvalidTracker.h"
#include "Networking/ConnectRequest.h"
#include "Networking/ConnectResponse.h"
#include "Networking/Networking.h"

#include <iostream>

Tracker::Tracker(URL* trackerURL)
: connectionID(trackerURL)
{
	// Currently, only upd trackers are supported
	if (trackerURL->protocol() != "udp")
	{
		throw InvalidTracker("Only supports UDP trackers.");
	}

	// If no port number is specified assume port 80
	if (trackerURL->port() == "")
	{
		trackerURL->setPort(80);
	}

	// Store the URL
	this->trackerURL = trackerURL;

cout << "Connection ID: " << this->getConnectionID() << endl;
}

uint64_t Tracker::getConnectionID()
{
	return this->connectionID.getValue();
}
