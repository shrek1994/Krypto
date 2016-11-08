#include "KeyReader.hpp"
#include "KeyInstaler.hpp"
#include "CryptionMain.hpp"
#include "CryptionAesCbc.hpp"

#include "debug.h"

Key KeyReader::readKey()
{
    constexpr long unsigned MAX_KEY_LENGTH = CryptoPP::AES::DEFAULT_KEYLENGTH;
    std::string pass;
    char password[MAX_KEY_LENGTH] = {0};
    outStream << "Podaj haslo do szyfowania: " << std::flush;
    CryptionMain::hideStdinKeystrokes();
    inStream >> pass;
    outStream << "\n";
    CryptionMain::showStdinKeystrokes();

    std::memcpy(password, pass.c_str(), std::min(MAX_KEY_LENGTH, pass.length()));

    CryptoPP::SecByteBlock passwordKey((byte*)password, MAX_KEY_LENGTH);
    CryptoPP::SecByteBlock initialVector(CONST::initialVectorByte, MAX_KEY_LENGTH);

    AES_CBC cbc(passwordKey, initialVector);

    Key key;

    auto decryptedKey = cbc.decrypt(in);

    LOG << decryptedKey.str() << "\n";

    for (int i = 0; i < CryptoPP::AES::DEFAULT_KEYLENGTH; i++)
    {
        key.key[i] = decryptedKey.get();
        key.iv[i] = decryptedKey.get();
    }

    return std::move(key);
}
