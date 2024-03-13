#include "gtest/gtest.h"
#include "util.hpp"

TEST(DataManipulationTests, AppendVector)
{
    uint16_t wrd(0xA5C3);
    std::vector<uint8_t> u_vec;
    util::appendword2vector(wrd, u_vec);

    EXPECT_EQ(u_vec[0], 0xA5);
    EXPECT_EQ(u_vec[1], 0xC3);
}

TEST(DataManipulationTests, Bytes2Word)
{
    uint8_t byt0(0xA5), byt1(0xC3);

    auto wrd1 = util::word_frombytes(byt0, byt1, false);
    EXPECT_EQ(wrd1, 0xA5C3);

    auto wrd2 = util::word_frombytes(byt0, byt1, true);
    EXPECT_EQ(wrd2, 0xC3A5);
}
