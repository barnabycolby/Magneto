#include "gtest/gtest.h"

#include "Networking/URL.h"
#include "Networking/InvalidURL.h"

TEST(URLTest, EmptyString)
{
	ASSERT_THROW(URL(""), InvalidURL);
}

TEST(URLTest, NoColonSlashSlash)
{
	ASSERT_THROW(URL("udp:/google.com:87/test"), InvalidURL);
}

TEST(URLTest, NoHost)
{
	ASSERT_THROW(URL("udp://:32/test?monkey=yay"), InvalidURL);
}

TEST(URLTest, NoProtocol)
{
	ASSERT_THROW(URL("://www.torrent.com/nothing?x=y"), InvalidURL);
}

TEST(URLTest, InvalidPort)
{
	ASSERT_THROW(URL("http://www.torrent.com:/tickle?x=y"), InvalidURL);
}

// Valid tests

TEST(URLTest, NoPort)
{
	ASSERT_NO_THROW({
		URL url("udp://www.google.com/tracker?id=1");
		EXPECT_EQ("udp", url.protocol());
		EXPECT_EQ("www.google.com", url.host());
		EXPECT_EQ("", url.port());
		EXPECT_EQ("tracker", url.path());
		EXPECT_EQ("id=1", url.query());
	});
}

TEST(URLTest, NoPath)
{
	ASSERT_NO_THROW({
		URL url("udp://www.google.com:6881/?id=1");
		EXPECT_EQ("udp", url.protocol());
		EXPECT_EQ("www.google.com", url.host());
		EXPECT_EQ("6881", url.port());
		EXPECT_EQ("", url.path());
		EXPECT_EQ("id=1", url.query());
	});
}

TEST(URLTest, NoQuery)
{
	ASSERT_NO_THROW({
		URL url("udp://www.google.com:789/tracker");
		EXPECT_EQ("udp", url.protocol());
		EXPECT_EQ("www.google.com", url.host());
		EXPECT_EQ("789", url.port());
		EXPECT_EQ("tracker", url.path());
		EXPECT_EQ("", url.query());
	});
}

TEST(URLTest, NoPathOrQuery1)
{
	ASSERT_NO_THROW({
		URL url("udp://www.google.com");
		EXPECT_EQ("udp", url.protocol());
		EXPECT_EQ("www.google.com", url.host());
		EXPECT_EQ("", url.port());
		EXPECT_EQ("", url.path());
		EXPECT_EQ("", url.query());
	});
}

TEST(URLTest, NoPathOrQuery2)
{
	ASSERT_NO_THROW({
		URL url("udp://www.google.com/");
		EXPECT_EQ("udp", url.protocol());
		EXPECT_EQ("www.google.com", url.host());
		EXPECT_EQ("", url.port());
		EXPECT_EQ("", url.path());
		EXPECT_EQ("", url.query());
	});
}

TEST(URLTest, NoPathOrQuery3)
{
	ASSERT_NO_THROW({
		URL url("udp://www.google.com:80");
		EXPECT_EQ("udp", url.protocol());
		EXPECT_EQ("www.google.com", url.host());
		EXPECT_EQ("80", url.port());
		EXPECT_EQ("", url.path());
		EXPECT_EQ("", url.query());
	});
}

TEST(URLTest, NoPathOrQuery4)
{
	ASSERT_NO_THROW({
		URL url("udp://www.google.com:6880/");
		EXPECT_EQ("udp", url.protocol());
		EXPECT_EQ("www.google.com", url.host());
		EXPECT_EQ("6880", url.port());
		EXPECT_EQ("", url.path());
		EXPECT_EQ("", url.query());
	});
}

TEST(URLTest, URLDecode)
{
	ASSERT_NO_THROW({
		URL url("udp%3A%2F%2Ftracker.openbittorrent.com%3A80");
		EXPECT_EQ("udp", url.protocol());
		EXPECT_EQ("tracker.openbittorrent.com", url.host());
		EXPECT_EQ("80", url.port());
		EXPECT_EQ("", url.path());
		EXPECT_EQ("", url.query());
	});
}
