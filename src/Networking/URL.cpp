#include "Networking/URL.h"

#include "Networking/InvalidURL.h"

#include <cctype>
#include <stdexcept>
#include <sstream>

URL::URL(string url)
{
	// protocol://host:port/path?query
	// Parse the url

	// Decode the URL
	urldecode(&url);

	// Get the protocol
	int colonSlashSlashPos = url.find("://");
	if (colonSlashSlashPos == string::npos)
	{
		throw InvalidURL("Contained no ://");
	}

	this->protocol_ = url.substr(0, colonSlashSlashPos);
	if (this->protocol_ == "")
	{
		throw InvalidURL("No protocol in the URL");
	}

	// Get the host, and port if it exists
	int colonPos = url.find(':', colonSlashSlashPos + 3);
	size_t slashPos = string::npos;
	if (colonPos != string::npos)
	{
		// Get the host
		this->host_ = url.substr(colonSlashSlashPos + 3, colonPos - (colonSlashSlashPos + 3));

		// Get the port
		slashPos = url.find('/', colonPos + 1);
		this->port_ = url.substr(colonPos + 1, slashPos - (colonPos + 1));
		if (this->port_ == "")
		{
			throw InvalidURL("No port number specified after : operator");
		}
	}
	else
	{
		// No port number specified
		// Get the host
		slashPos = url.find('/', colonSlashSlashPos + 3);
		this->host_ = url.substr(colonSlashSlashPos + 3, slashPos - (colonSlashSlashPos + 3));
	}

	// Check that the host name is valid
	if (this->host_ == "")
	{
		throw InvalidURL("No hostname");
	}

	// Check for the case when there is no path or query
	if (slashPos == string::npos)
	{
		return;
	}

	// Get the path
	int questionMarkPos = url.find('?', slashPos + 1);
	if (questionMarkPos != string::npos)
	{
		this->path_ = url.substr(slashPos + 1, questionMarkPos - (slashPos + 1));

		// Get the query
		this->query_ = url.substr(questionMarkPos + 1, string::npos);
	}
	else
	{
		this->path_ = url.substr(slashPos + 1, string::npos);
		return;
	}
}

void URL::urldecode(string* url)
{
	// Every time we find a percent sign we need to decode it
	int percentPos = 0;
	while ((percentPos = url->find('%', percentPos)) != string::npos)
	{
		// Check whether the 2 characters following the sign are hexadecimal
		try {
			if (!isxdigit(url->at(percentPos + 1)) || !isxdigit(url->at(percentPos + 2)))
			{
				throw InvalidURL("Contained invalid URL encodings");
			}
		}
		catch (const out_of_range& e)
		{
			throw InvalidURL("Contained incomplete URL encodings");
		}

		// Convert the string to a char
		int i;
		stringstream ss;
		ss << std::hex << url->substr(percentPos + 1, 2);
		ss >> i;
		char c = i;
		const char c2 = c;
		string replacement(&c2);

		url->replace(percentPos, 3, replacement);
	}
}

string URL::protocol()
{
	return this->protocol_;
}

string URL::host()
{
	return this->host_;
}

string URL::port()
{
	return this->port_;
}

string URL::path()
{
	return this->path_;
}

string URL::query()
{
	return this->query_;
}

void URL::setPort(int port)
{
	this->port_ = to_string(port);
}
