#include "Networking/Networking.h"

#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "Networking/NetworkingTimeout.h"

#include <iostream>

using boost::asio::ip::udp;

// Takes a url-> a message to send, sends it asynchronously and then calls a callback function with the response
vector<unsigned char> Networking::syncSendUDPRequest(UDPRequest* request, URL* url, int timeout)
{
	// Make an io_service object
	boost::asio::io_service io;

	// We use a resolver object to find the correct endpoint based on the host and port number
	udp::resolver resolver(io);
	udp::resolver::query query(udp::v4(), url->host(), url->port());

	// Get the endpoint
	udp::endpoint receiver_endpoint = *resolver.resolve(query);

	// Create a socket to initiate contact
	udp::socket socket(io);
	socket.open(udp::v4());
	
	// Send the data
	socket.send_to(boost::asio::buffer(request->getRequest()), receiver_endpoint);

	// Get ready to receive the response
	// Currently the largest response length is 20 bytes
	// (http://www.bittorrent.org/beps/bep_0015.html)
	Networking::returnValue = vector<unsigned char>(20);
	udp::endpoint sender_endpoint;
	socket.async_receive_from(
		boost::asio::buffer(Networking::returnValue),
		sender_endpoint,
		boost::bind(&Networking::handle_receive,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));

	// Set the timer
	boost::asio::deadline_timer timer(io, boost::posix_time::seconds(timeout));
	timer.async_wait(&handle_timeout);

	// Run the async waits
	io.run_one();

	// Return the response
	return Networking::returnValue;
}

vector<unsigned char> Networking::returnValue;

void Networking::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	Networking::returnValue.resize(bytes_transferred);
}

void Networking::handle_timeout(const boost::system::error_code& error)
{
	throw NetworkingTimeout();
}
