#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "CryptionAesCtr.hpp"

#include <cryptopp/aes.h>

#include <string>
#include <sstream>

#include "extensiontest.h"

namespace {
const char text[] = "Hello World !!!\nEncrypt Test!";
const std::string textString = text;
const byte encryptedText[] = {0xB1, 0x27, 0x11, 0x1F, 0x7D, 0xA5, 0x3D, 0x21, 0x60, 0x97, 0x33, 0x4F, 0xB8, 0xA7,
                              0xD6, 0x85, 0x51, 0x58, 0xE7, 0xB6, 0xDC, 0x3F, 0x2D, 0x4A, 0x97, 0xA1, 0x91, 0x88,
                              0x95, 0x0};
const byte keyByte[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x90 };
const byte ivByte[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0x98, 0x76, 0x54, 0x32, 0x10 };

class CryptionCRTTest : public ::testing::Test {

protected:
    CryptoPP::SecByteBlock key = {keyByte, sizeof(keyByte)};
    CryptoPP::SecByteBlock iv =  {ivByte, sizeof(ivByte)};
    AES_CTR sut = {key, iv};
};

TEST_F(CryptionCRTTest, encryptFile)
{
    std::stringstream in(text);

    auto out = sut.encrypt(in);
    EXPECT_BYTEEQ(encryptedText, out.str().c_str());
}

TEST_F(CryptionCRTTest, decryptFile)
{
    std::stringstream in;
    in << encryptedText;

    auto out = sut.decrypt(in);
    EXPECT_BYTEEQ(text, out.str().c_str());
}

TEST_F(CryptionCRTTest, encryptAndDecryptFile)
{
    std::stringstream in(text);

    auto outEncrypted = sut.encrypt(in);
    auto out = sut.decrypt(outEncrypted);

    EXPECT_BYTEEQ(text, out.str().c_str());
}

} //namespace
