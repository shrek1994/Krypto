#include "CryptionFactory.hpp"
#include "CryptionAesCbc.hpp"
#include "CryptionAesCtr.hpp"
#include "CryptionAesGcm.hpp"
#include <iostream>



CryptionFactory::CryptionFactory(std::string cryption){
    if (cryption == "CBC" || cryption == "cbc")
    {
        this->cryption = Cryption::CBC;
    }
    else if (cryption == "CTR" || cryption == "ctr")
    {
        this->cryption = Cryption::CTR;
    }
    else
    {
        std::cerr << "Wrong cryption mode: " << cryption << std::endl;
    }

}

std::shared_ptr<ICryption> CryptionFactory::create(CryptoPP::SecByteBlock &key, CryptoPP::SecByteBlock &iv)
{
    switch (cryption)
    {
        case Cryption::CBC:
            return std::make_shared<CryptionAesCbc>(key, iv);
        case Cryption::CTR:
            return std::make_shared<CryptionAesCtr>(key, iv);
    }
}
