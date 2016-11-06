#include "CryptionAesGcm.hpp"

#include <string>
#include <cryptopp/gcm.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>

#include "debug.h"

std::stringstream CryptionAesGcm::encrypt(std::istream &in)
{
    using namespace CryptoPP;

    std::stringstream out;
    std::string cipherFile, pdata;

    try
    {
        GCM<AES>::Encryption encryption;
        encryption.SetKeyWithIV(key, key.size(), iv, iv.size());
        FileSource fs(in,
                      true,
                      new AuthenticatedEncryptionFilter(encryption,
                          new StringSink(cipherFile), false, TAG_SIZE));
//        StringSource ss1( pdata, true,
//            new AuthenticatedEncryptionFilter( e,
//                new StringSink( cipherFile ), false, TAG_SIZE
//            ) // AuthenticatedEncryptionFilter
//        ); // StringSource

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

std::stringstream CryptionAesGcm::decrypt(std::istream &in)
{
    using namespace CryptoPP;
    std::stringstream out;
    std::string recoveredFile;

    try
    {
        GCM< AES >::Decryption decryption;
        decryption.SetKeyWithIV( key, key.size(), iv );

        AuthenticatedDecryptionFilter df( d,
            new StringSink( rpdata ),
            AuthenticatedDecryptionFilter::Flags::DEFAULT_FLAGS, TAG_SIZE
        ); // AuthenticatedDecryptionFilter

        LOG << "recovered text: " << recoveredFile << std::endl;
        out << recoveredFile;
    }
    catch( const CryptoPP::Exception& e )
    {
        std::cerr << e.what() << std::endl;
    }

    return std::move(out);
}
