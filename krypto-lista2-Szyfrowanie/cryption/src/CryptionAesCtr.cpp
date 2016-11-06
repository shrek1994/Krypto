#include "CryptionAesCtr.hpp"
#include <openssl/aes.h>
#include <stdio.h>
#include <string.h>


#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>

#include <iostream>
#include "debug.h"


std::stringstream CryptionAesCtr::encrypt(std::istream &in)
{
    using namespace CryptoPP;

    std::stringstream out;
    std::string cipherFile;

    try
    {
        CTR_Mode<AES>::Encryption encryption;
        encryption.SetKeyWithIV(key, key.size(), iv);
        FileSource fs(in,
                      true,
                      new StreamTransformationFilter(encryption,
                                                     new StringSink(cipherFile)));

        LOG << "Encrypted file: \n";
        printHex(cipherFile.c_str());

        out << cipherFile;
    }
    catch(const CryptoPP::Exception& e )
    {
        std::cerr << e.what() << std::endl;
    }

    return std::move(out);

}

std::stringstream CryptionAesCtr::decrypt(std::istream &in)
{
    using namespace CryptoPP;
    std::stringstream out;
    std::string recoveredFile;

    try
    {
        CTR_Mode< AES >::Decryption decryption;
        decryption.SetKeyWithIV( key, key.size(), iv );

        FileSource fs (in,
                       true,
                       new StreamTransformationFilter(decryption,
                                                      new StringSink(recoveredFile)));

        LOG << "recovered text: " << recoveredFile << std::endl;
        out << recoveredFile;
    }
    catch( const CryptoPP::Exception& e )
    {
        std::cerr << e.what() << std::endl;
    }

    return std::move(out);
}
