#ifndef ENCRYPTIONAES_CBS_H
#define ENCRYPTIONAES_CBS_H

#include "ICryption.hpp"
#include <cryptopp/secblock.h>

class CryptionAesCbc : public ICryption
{
public:
    CryptionAesCbc(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv)
        : key(std::move(key)),
          iv(std::move(iv))
    {
    }

    std::stringstream encrypt(std::istream& in) override;
    std::stringstream decrypt(std::istream& in) override;

private:
    CryptoPP::SecByteBlock key;
    CryptoPP::SecByteBlock iv;
};

typedef CryptionAesCbc AES_CBC;

#endif // ENCRYPTIONAES_CBS_H
