#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "CryptionAesGcm.hpp"

#include <cryptopp/aes.h>

#include <string>
#include <sstream>

#include "extensiontest.h"

namespace {
const char text[] = "Hello World !!!\nEncrypt Test!";
const std::string textString = text;
const byte encryptedText[] = {0xA8, 0xD0, 0xEE, 0x6F, 0x8C, 0x28, 0x4C, 0xF5, 0x3C, 0x13, 0x9, 0x49, 0xA4, 0x7F, 0xE1,
                              0x9D, 0xB4, 0xDE, 0xA9, 0x27, 0xB2, 0x9E, 0x49, 0x35, 0xAC, 0x27, 0x36, 0xF2, 0x48, 0xCD,
                              0x41, 0xCC, 0x48, 0x19, 0xE4, 0xF7, 0xB2, 0x5A, 0x90, 0xC, 0x18, 0x0};

const byte keyByte[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x90 };
const byte ivByte[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0x98, 0x76, 0x54, 0x32, 0x10 };

class CryptionGCMTest : public ::testing::Test {

protected:
    CryptoPP::SecByteBlock key = {keyByte, sizeof(keyByte)};
    CryptoPP::SecByteBlock iv =  {ivByte, sizeof(ivByte)};
    AES_GCM sut = {key, iv};
};

TEST_F(CryptionGCMTest, DISABLED_encryptFile)
{
    std::stringstream in(text);

    auto out = sut.encrypt(in);
    EXPECT_BYTEEQ(encryptedText, out.str().c_str());
}

TEST_F(CryptionGCMTest, DISABLED_decryptFile)
{
    std::stringstream in;
    in << encryptedText;

    auto out = sut.decrypt(in);
    EXPECT_BYTEEQ(text, out.str().c_str());
}

TEST_F(CryptionGCMTest, DISABLED_encryptAndDecryptFile)
{
    std::stringstream in(text);

    auto outEncrypted = sut.encrypt(in);
    auto out = sut.decrypt(outEncrypted);

    EXPECT_BYTEEQ(text, out.str().c_str());
}

} //namespace
