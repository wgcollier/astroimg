#include <gtest/gtest.h>
#include "ccsdspacket.hpp"

TEST(PrimaryHeaderTests, UnsegmentedCommand)
{
	CcsdsPrimaryHeader hdr(cmd, false, 0xD0, 17, unsegmented, 1);


	EXPECT_TRUE(hdr.isCommand());
	EXPECT_FALSE(hdr.isTelemetry());
	EXPECT_FALSE(hdr.isSegmented());
	EXPECT_FALSE(hdr.isContinuation());
	EXPECT_FALSE(hdr.isLastSegment());
	EXPECT_EQ(hdr.get_appid(), 0xD0);
	EXPECT_EQ(hdr.get_sequencenumber(), 1);
	EXPECT_EQ(hdr.get_size(), 17);
}
