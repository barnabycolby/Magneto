#ifndef CONNECTION_ID_H
#define CONNECTION_ID_H

#include "VariableTimeout/VariableTimeout.h"

#include "Networking/URL.h"

#include <cstdint>

using namespace std;

class ConnectionID : public VariableTimeout<uint64_t>
{
public:
	ConnectionID(URL* trackerURL);

private:
	uint64_t obtain();

private:
	URL* trackerURL;
};

#endif
