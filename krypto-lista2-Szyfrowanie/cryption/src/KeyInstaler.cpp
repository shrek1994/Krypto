#include "KeyInstaler.hpp"
#include "CryptionAesCbc.hpp"
#include <sstream>
#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include "CryptionMain.hpp"

#include "debug.h"

void KeyInstaler::install()
{
    constexpr long unsigned MAX_KEY_LENGTH = CryptoPP::AES::DEFAULT_KEYLENGTH;
    std::string pass;
    char password[MAX_KEY_LENGTH] = {0};
    std::cout << "Podaj haslo do szyfowania :" << std::flush;
    CryptionMain::hideStdinKeystrokes();
    in >> pass;
    CryptionMain::showStdinKeystrokes();

    std::memcpy(password, pass.c_str(), std::min(MAX_KEY_LENGTH, pass.length()));

    CryptoPP::SecByteBlock passwordKey((byte*)password, MAX_KEY_LENGTH);
    CryptoPP::SecByteBlock initialVector(CONST::initialVectorByte, MAX_KEY_LENGTH);

    AES_CBC cbc(passwordKey, initialVector);

    // generowanie klucza i iv
//    CryptoPP::AutoSeededRandomPool random;

    byte key[MAX_KEY_LENGTH];
    random->GenerateBlock(key, sizeof(key));

    byte iv[MAX_KEY_LENGTH];
    random->GenerateBlock(iv, sizeof(iv));

    std::stringstream keyStream;
    for (int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; i++)
    {
        keyStream << key[i] << iv[i];
    }

//    LOG << keyStream.str() << "\n";

    auto keyencrypted = cbc.encrypt(keyStream);

    out << keyencrypted.str();
}
