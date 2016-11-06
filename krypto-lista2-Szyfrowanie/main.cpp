#ifdef TESTING

#include <gtest/gtest.h>

int main(int numOfArg, char *args[])
{
    ::testing::InitGoogleTest(&numOfArg, args);
    return RUN_ALL_TESTS();
}

#else

#include <iostream>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>

#include "debug.h"
#include <cryptopp/gcm.h>
#include "CryptionMain.hpp"

namespace {
const byte keyByte[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x90 };
const byte ivByte[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0x98, 0x76, 0x54, 0x32, 0x10 };

const CryptoPP::SecByteBlock key = {keyByte, sizeof(keyByte)};
const CryptoPP::SecByteBlock iv =  {ivByte, sizeof(ivByte)};
}

int main(int numOfArg, char* args[])
{
    CryptionMain m;
    m.run(numOfArg, args);
    return 0;
}

#endif
