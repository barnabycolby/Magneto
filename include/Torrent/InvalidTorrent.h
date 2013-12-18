#ifndef INVALID_TORRENT_H
#define INVALID_TORRENT_H

#include <exception>

class InvalidTorrent: public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Torrent was invalid.";
	}
};

#endif
