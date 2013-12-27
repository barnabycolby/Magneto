#include "gtest/gtest.h"

#include "Tracker/Tracker.h"
#include "Tracker/InvalidTracker.h"
#include "Networking/InvalidURL.h"
#include "Networking/NetworkingTimeout.h"

#include <iostream>

TEST(TrackerTest, TCP)
{
	// No TCP Tracker support currently
	URL tcp("tcp://localhost:6881");
	EXPECT_THROW(new Tracker(&tcp), InvalidTracker);
}

TEST(TrackerTest, MadeUpURL)
{
	// Made up tracker
	URL madeUp("udp://barneysTracker.com:1234");
	EXPECT_THROW(new Tracker(&madeUp), InvalidTracker);
}

// Disabled because it takes a minute to run
TEST(TrackerTest, TimeOut)
{
	// This url should timeout
	// It requires the UDPServer program to be running locally, which simply receives messages and doesn't send anything back
	URL timeOut("udp://localhost:22222");
	EXPECT_THROW(new Tracker(&timeOut), NetworkingTimeout);
}

TEST(TrackerTest, ValidURLs)
{
	// We can assume a port number of 80 for URLs with no port number
	URL noPort("udp://tracker.openbittorrent.com");
	EXPECT_NO_THROW(new Tracker(&noPort));

	// A real tracker with URL taken from website
	URL valid("udp://tracker.publicbt.com:80/announce");
	EXPECT_NO_THROW(new Tracker(&valid));
}
