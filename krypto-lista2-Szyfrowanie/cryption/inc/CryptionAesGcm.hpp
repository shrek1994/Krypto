#ifndef ENCRYPTIONAESGCM_H
#define ENCRYPTIONAESGCM_H

#include "ICryption.hpp"
#include <cryptopp/secblock.h>


class CryptionAesGcm : public ICryption
{
public:
    CryptionAesGcm(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv)
        : key(std::move(key)),
          iv(std::move(iv)) {}

    std::stringstream encrypt(std::istream& in) override;
    std::stringstream decrypt(std::istream& in) override;

private:
    CryptoPP::SecByteBlock key;
    CryptoPP::SecByteBlock iv;
    const int TAG_SIZE = 12;
};

typedef CryptionAesGcm AES_GCM;

#endif // ENCRYPTIONAESGCM_H
