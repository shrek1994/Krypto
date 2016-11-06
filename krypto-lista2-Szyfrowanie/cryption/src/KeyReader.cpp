#include "KeyReader.hpp"
#include "KeyInstaler.hpp"
#include "CryptionMain.hpp"
#include "CryptionAesCbc.hpp"


Key KeyReader::readKey()
{
    char password[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0};
    std::cout << "Podaj haslo do szyfowania :" << std::flush;
    CryptionMain::hideStdinKeystrokes();
    std::cin >> password;
    CryptionMain::showStdinKeystrokes();


    CryptoPP::SecByteBlock passwordKey((byte*)password, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::SecByteBlock initialVector(CONST::initialVectorByte, CryptoPP::AES::DEFAULT_KEYLENGTH);

    AES_CBC cbc(passwordKey, initialVector);

    Key key;

    auto decryptedKey = cbc.decrypt(in);
    decryptedKey >> key.key >> key.iv;

    return std::move(key);
}
