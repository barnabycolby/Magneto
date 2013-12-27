#ifndef UDP_RESPONSE_H
#define UDP_RESPONSE_H

#include <cstdint>
#include <vector>

using namespace std;

class UDPResponse
{
public:
	UDPResponse(vector<unsigned char>* response);
private:
	vector<unsigned char>* response;
	vector<unsigned char>::iterator it;

public:
	uint32_t get32BitInt();
	uint64_t get64BitInt();
	unsigned char getNextByte();
};

#endif
