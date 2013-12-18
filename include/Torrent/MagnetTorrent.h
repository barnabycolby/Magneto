#ifndef MAGNET_TORRENT_H
#define MAGNET_TORRENT_H

#include <string>
#include <queue>

using namespace std;

class MagnetTorrent
{
public:
	// Constructor
	MagnetTorrent(string link);	

	// Getters and Setters
	string getInfoHash();
	string getDisplayName();
	queue<string>* getTrackers();

private:
	string infoHash;
	string displayName;
	queue<string> trackers;

	bool containsEqualOrAmpersand(string value);
};

#endif
