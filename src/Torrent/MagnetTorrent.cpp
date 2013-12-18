#include "Torrent/MagnetTorrent.h"
#include "Torrent/InvalidTorrent.h"

#include <boost/algorithm/string.hpp>

// Constructor
MagnetTorrent::MagnetTorrent(string link)
{
	// String cannot be empty
	if (link == "")
	{
		throw InvalidTorrent();
	}

	// It should start with magnet:?
	if (!boost::starts_with(link, "magnet:?"))
	{
		throw InvalidTorrent();	
	}

	// We can remove magnet:? and start parsing parameters
	link.erase(0, 8);

	while (link.length() > 0)
	{
		// Get the parameter name
		int equalsPos = link.find('=');
		string paramName = link.substr(0, equalsPos);

		// Check validity of value
		if(containsEqualOrAmpersand(paramName))
		{
			throw InvalidTorrent();
		}
		
		// Erase the name and equals sign
		link.erase(0, equalsPos + 1);
		
		// Get the parameters value
		string value;
		int andPos = link.find('&');
		if (andPos == string::npos)
		{
			value = link;	

			// Erase the value
			link = "";
		}
		else
		{
			value = link.substr(0, andPos);

			// Erase the value and ampersand
			link.erase(0, andPos + 1);
		}

		// Check validity of value
		if (containsEqualOrAmpersand(value))
		{
			throw InvalidTorrent();
		}
		
		if (paramName == "xt")
		{
			// The xt parameter must start with urn:btih:
			if(!boost::starts_with(value, "urn:btih:"))
			{
				throw InvalidTorrent();
			}

			// Remove the urn:btih: prefix
			value.erase(0, 9);

			this->infoHash = value;
		}
		else if (paramName == "dn")
		{
			this->displayName = value;
		}
		else if (paramName == "tr")
		{
			this->trackers.push(value);
		}
	}

	// The xt parameter is mandatory
	if (this->getInfoHash() == "")
	{
		throw InvalidTorrent();
	}
}

string MagnetTorrent::getInfoHash()
{
	return this->infoHash;
}

string MagnetTorrent::getDisplayName()
{
	return this->displayName;
}

queue<string>* MagnetTorrent::getTrackers()
{
	return &(this->trackers);
}

bool MagnetTorrent::containsEqualOrAmpersand(string str)
{
	return ((str.find('=') != string::npos) || (str.find('&') != string::npos));
}
