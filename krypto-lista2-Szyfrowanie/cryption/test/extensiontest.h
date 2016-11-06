#pragma once

#define EXPECT_BYTEEQ(expected, result) \
    for(auto i = 0 ; i < sizeof(expected); ++i) \
        EXPECT_EQ((byte)expected[i], (byte)result[i]) << "i = " << i << "/" << sizeof(expected) - 1

