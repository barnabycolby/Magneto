#include "gtest/gtest.h"

#include "Torrent/MagnetTorrent.h"
#include "Torrent/InvalidTorrent.h"

#include <string>
#include <iostream>

TEST(MagnetLinkTest, EmptyString)
{
	ASSERT_THROW(new MagnetTorrent(""), InvalidTorrent);
}

TEST(MagnetLinkTest, InvalidLinks)
{
	// Missing xt
	string missingXt = "magnet:?";
	EXPECT_THROW(new MagnetTorrent(missingXt), InvalidTorrent);

	// Missing magnet
	string missingMagnet = "xt=urn:btih:e10f4966a18b510c504fb661b927fbf744541de6&dn=displayName&tr=udp://tracker.openbittorrent.com:80/announce";
	EXPECT_THROW(new MagnetTorrent(missingMagnet), InvalidTorrent);

	// Has dn & tr but no xt
	string noXt = "magnet:?dn=displayName&tr=udp://tracker.openbittorrent.com:80/announce";
	EXPECT_THROW(new MagnetTorrent(noXt), InvalidTorrent);


	// Invalid sequence of ='s and &'s
	string invalidSequence1 = "magnet:?xt=urn:btih:e10f4966a18b510c504fb661b927fbf744541de6&dn=displayName=tr=udp://tracker.openbittorrent.com:80/announce";
	EXPECT_THROW(new MagnetTorrent(invalidSequence1), InvalidTorrent);

	// Invalid sequence of ='s and &'s
	string invalidSequence2= "magnet:?xt=urn:btih:e10f4966a18b510c504fb661b927fbf744541de6&dn=displayName&tr&udp://tracker.openbittorrent.com:80/announce";
	EXPECT_THROW(new MagnetTorrent(invalidSequence2), InvalidTorrent);

	// Invalid xt sequence
	string invalidXt = "magnet:?xt=e10f4966a18b510c504fb661b927fbf744541de6&dn=displayName&tr=udp://tracker.openbittorrent.com:80/announce";
	EXPECT_THROW(new MagnetTorrent(invalidXt), InvalidTorrent);
}

TEST(MagnetLinkTest, ValidLinks)
{
	// Check that a standard link works
	string standard = "magnet:?xt=urn:btih:e10f4966a18b510c504fb661b927fbf744541de6&dn=displayName&tr=udp://tracker.openbittorrent.com:80/announce";
	MagnetTorrent* t = new MagnetTorrent(standard);

	EXPECT_EQ("e10f4966a18b510c504fb661b927fbf744541de6", t->getInfoHash());
	EXPECT_EQ("displayName", t->getDisplayName());
	EXPECT_EQ("udp://tracker.openbittorrent.com:80/announce", t->getTrackers()->front());
	t->getTrackers()->pop();

	// Test multiple trackers
	string multipleTrackers = "magnet:?xt=urn:btih:e10f4966a18b510c504fb661b927fbf744541de6&dn=displayName&tr=udp://tracker.openbittorrent.com:80/announce&tr=udp://9.rarbg.com:2710/announce&tr=udp://fr33dom.h33t.com:3310/announce";
	t = new MagnetTorrent(multipleTrackers);
	EXPECT_EQ("e10f4966a18b510c504fb661b927fbf744541de6", t->getInfoHash());
	EXPECT_EQ("displayName", t->getDisplayName());
	EXPECT_EQ("udp://tracker.openbittorrent.com:80/announce", t->getTrackers()->front());
	t->getTrackers()->pop();
	EXPECT_EQ("udp://9.rarbg.com:2710/announce", t->getTrackers()->front());
	t->getTrackers()->pop();
	EXPECT_EQ("udp://fr33dom.h33t.com:3310/announce", t->getTrackers()->front());
	t->getTrackers()->pop();
}
