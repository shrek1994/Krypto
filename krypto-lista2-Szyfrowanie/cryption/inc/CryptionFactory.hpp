#ifndef CRYPTIONFACTORY_H
#define CRYPTIONFACTORY_H
#include <string>
#include <memory>
#include "ICryption.hpp"
#include <cryptopp/secblock.h>

enum class Cryption
{
    CBC,
    CTR
//    ,
//    GCM
};


class CryptionFactory
{
public:
    CryptionFactory(std::string cryption);

    std::shared_ptr<ICryption> create(CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& iv);


private:
    Cryption cryption = Cryption::CBC;
};

#endif // CRYPTIONFACTORY_H
