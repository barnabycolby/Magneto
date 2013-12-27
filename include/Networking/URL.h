#ifndef URL_H
#define URL_H

#include <string>

using namespace std;

class URL
{
public:
	URL(string url);

private:
	string protocol_;
	string host_;
	string port_;
	string path_;
	string query_;

public:
	string protocol();
	string host();
	string port();
	string path();
	string query();

	void setPort(int port);

private:
	void urldecode(string* url);
};

#endif
