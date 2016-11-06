#ifndef ENCRYPTIONAES_CTR_H
#define ENCRYPTIONAES_CTR_H
#include "ICryption.hpp"
#include <cryptopp/secblock.h>

class CryptionAesCtr : public ICryption
{
public:
    CryptionAesCtr(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv)
        : key(std::move(key)),
          iv(std::move(iv)) {}

    std::stringstream encrypt(std::istream& in) override;
    std::stringstream decrypt(std::istream& in) override;

private:
    CryptoPP::SecByteBlock key;
    CryptoPP::SecByteBlock iv;
};

typedef CryptionAesCtr AES_CTR;

#endif // ENCRYPTIONAES_CTR_H
