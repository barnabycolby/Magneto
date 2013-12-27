#ifndef TRACKER_H
#define TRACKER_H

#include "Networking/UDPResponse.h"
#include "Networking/URL.h"
#include "Tracker/ConnectionID.h"

#include <cstdint>
#include "boost/asio.hpp"

class Tracker
{
public:
	Tracker(URL* trackerURL);

private:
	URL* trackerURL;
	ConnectionID connectionID;

private:
	uint64_t getConnectionID();
};

#endif
