#ifndef KEYREADER_H
#define KEYREADER_H

#include <iostream>
#include <cryptopp/aes.h>

struct Key
{
    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0};
    byte iv[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0};
};

class KeyReader
{
public:
    KeyReader(std::istream& inFile, std::istream& inStream = std::cin)
        : in(inFile), inStream(inStream) {}

    Key readKey();

private:
    std::istream& in;
    std::istream& inStream;
};

#endif // KEYREADER_H
