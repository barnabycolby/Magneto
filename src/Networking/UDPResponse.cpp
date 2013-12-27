#include "Networking/UDPResponse.h"

UDPResponse::UDPResponse(vector<unsigned char>* response)
{
	// Store the response so it can be parsed later
	this->response = response;

	// Create an iterator so that calls to get32BitInt or get64BitInt don't consider bytes that have already been considered
	this->it = this->response->begin();

	// We don't know how the response should be split
	// It is different based on the type of response
	// A constructor to do this should be written by the classes extending this one
}

uint32_t UDPResponse::get32BitInt()
{
 	uint32_t first  = (this->getNextByte() << 24) & 0xFF000000;
	uint32_t second = (this->getNextByte() << 16) & 0x00FF0000;
	uint32_t third  = (this->getNextByte() <<  8) & 0x0000FF00;
	uint32_t fourth = this->getNextByte() & 0x000000FF;

	return (first + second + third + fourth);
}

unsigned char UDPResponse::getNextByte()
{
	unsigned char v = *(this->it);
	(this->it)++;
	return v;
}

uint64_t UDPResponse::get64BitInt()
{
	uint64_t first = (((uint64_t)this->get32BitInt()) << 32) & 0xFFFFFFFF00000000;
	uint64_t second = (uint64_t)this->get32BitInt();

	return (first + second);
}
