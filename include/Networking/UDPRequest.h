#ifndef UDP_REQUEST_H
#define UDP_REQUEST_H

#include <cstdint>
#include <vector>

using namespace std;

class UDPRequest
{
public:
	UDPRequest();

protected:
	vector<unsigned char> request;
	uint32_t transaction_id;

public:
	void add32BitInt(uint32_t theInt);
	void add64BitInt(uint64_t theInt);
	uint32_t generateRandom32BitInt();

	vector<unsigned char> getRequest();
	uint32_t getTransactionID();
};

#endif
