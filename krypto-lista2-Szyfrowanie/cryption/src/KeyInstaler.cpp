#include "KeyInstaler.hpp"
#include "CryptionAesCbc.hpp"
#include <sstream>
#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include "CryptionMain.hpp"


void KeyInstaler::install()
{
    char password[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0};
    std::cout << "Podaj haslo do szyfowania :" << std::flush;
    CryptionMain::hideStdinKeystrokes();
    std::cin >> password;
    CryptionMain::showStdinKeystrokes();

    CryptoPP::SecByteBlock passwordKey((byte*)password, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::SecByteBlock initialVector(CONST::initialVectorByte, CryptoPP::AES::DEFAULT_KEYLENGTH);

    AES_CBC cbc(passwordKey, initialVector);

    // generowanie klucza i iv
    CryptoPP::AutoSeededRandomPool random;

    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    random.GenerateBlock(key, sizeof(key));

    byte iv[ CryptoPP::AES::BLOCKSIZE ];
    random.GenerateBlock(iv, sizeof(iv));

    std::stringstream keyStream;
    keyStream << key << "\n" << iv;

    auto keyencrypted = cbc.encrypt(keyStream);

    out << keyencrypted.str();
}
