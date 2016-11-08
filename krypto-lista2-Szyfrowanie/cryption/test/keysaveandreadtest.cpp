#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <sstream>
#include "KeyInstaler.hpp"
#include "KeyReader.hpp"
#include <string>
#include <memory>
#include "extensiontest.h"

namespace {
const byte KEY[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
const byte IV[] = {21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
const std::string password = "haslo123!@#";


class RandomMock : public CryptoPP::AutoSeededRandomPool
{
    void GenerateBlock(byte* output, size_t size) override
    {
        static int i = 0;
        if ( i % 2 == 0)
            std::memcpy(output, KEY, size);
        else
            std::memcpy(output, IV, size);
        i++;
    }
};

class KeySaveAndReadTest : public ::testing::Test {
public:
    std::stringstream file;
    std::stringstream standardIn;
    std::stringstream standardOut;
    std::shared_ptr<RandomMock> randomMock = std::make_shared<RandomMock>();
    std::unique_ptr<KeyInstaler> installer = std::make_unique<KeyInstaler>(file, standardIn, randomMock, standardOut);
    std::unique_ptr<KeyReader> reader = std::make_unique<KeyReader>(file, standardIn, standardOut);
};

TEST_F(KeySaveAndReadTest, saveAndRead) {

    standardIn << password << "\n";
    installer->install();

    standardIn << password << "\n";
    Key key = reader->readKey();

    EXPECT_BYTEEQ(KEY, key.key);
    EXPECT_BYTEEQ(IV, key.iv);
}

}  // namespace
