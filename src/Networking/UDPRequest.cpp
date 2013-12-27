#include "Networking/UDPRequest.h"

#include "boost/random/mersenne_twister.hpp"
#include "boost/random/uniform_int_distribution.hpp"

#include <ctime>
#include <iostream>
#include <algorithm>

UDPRequest::UDPRequest()
{
	this->transaction_id = this->generateRandom32BitInt();
}

void UDPRequest::add32BitInt(uint32_t theInt)
{
	unsigned char first  = (theInt & 0xFF000000) >> 24;
	unsigned char second = (theInt & 0x00FF0000) >> 16;
	unsigned char third  = (theInt & 0x0000FF00) >> 8;
	unsigned char fourth = (theInt & 0x000000FF) >> 0;

	this->request.push_back(first);
	this->request.push_back(second);
	this->request.push_back(third);
	this->request.push_back(fourth);
}

void UDPRequest::add64BitInt(uint64_t theInt)
{
	// Split the 64 bit int into 2 32 bit ints
	uint32_t first = (theInt & 0xFFFFFFFF00000000) >> 32;
	uint32_t second = (theInt & 0xFFFFFFFF) >> 0;	

	// Add them to the request structure
	this->add32BitInt(first);
	this->add32BitInt(second);
}

vector<unsigned char> UDPRequest::getRequest()
{
	return this->request;
}

uint32_t UDPRequest::generateRandom32BitInt()
{
	boost::mt19937 gen(std::time(0));
	boost::random::uniform_int_distribution<uint32_t> dist(0, std::numeric_limits<uint32_t>::max());
	return dist(gen);
}

uint32_t UDPRequest::getTransactionID()
{
	return this->transaction_id;
}
