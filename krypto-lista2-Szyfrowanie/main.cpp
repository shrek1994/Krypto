#ifdef TESTING

#include <gtest/gtest.h>

int main(int numOfArg, char *args[])
{
    ::testing::InitGoogleTest(&numOfArg, args);
    return RUN_ALL_TESTS();
}

#else

#include <iostream>

#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>

#include "debug.h"
#include <cryptopp/gcm.h>

namespace {

const byte keyByte[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x90 };
const byte ivByte[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0x98, 0x76, 0x54, 0x32, 0x10 };

const CryptoPP::SecByteBlock key = {keyByte, sizeof(keyByte)};
const CryptoPP::SecByteBlock iv =  {ivByte, sizeof(ivByte)};
}



int main(int numOfArg, char* args[])
{
    using namespace std;
    using namespace CryptoPP;

    string plain = "Hello World !!!\nEncrypt Test!";
    string cipher, encoded, recovered;

    const int TAG_SIZE = 12;

    // Plain text
    string pdata=plain;//"Authenticated Encryption";

    // Encrypted, with Tag
//    string cipher, encoded;

    // Recovered plain text
    string rpdata;

    /*********************************\
    \*********************************/

    try
    {
        GCM< AES >::Encryption e;
        e.SetKeyWithIV( key, key.size(), iv, sizeof(iv) );

        StringSource ss1( pdata, true,
            new AuthenticatedEncryptionFilter( e,
                new StringSink( cipher ), false, TAG_SIZE
            ) // AuthenticatedEncryptionFilter
        ); // StringSource
    }
    catch( CryptoPP::Exception& e )
    {
        cerr << e.what() << endl;
        exit(1);
    }

    cout << "cipher text: " << encoded << endl;
    printHex(cipher.c_str());

    /*********************************\
    \*********************************/

    try
    {
        GCM< AES >::Decryption d;
        d.SetKeyWithIV( key, key.size(), iv, sizeof(iv) );

        AuthenticatedDecryptionFilter df( d,
            new StringSink( rpdata ),
            AuthenticatedDecryptionFilter::Flags::DEFAULT_FLAGS, TAG_SIZE
        ); // AuthenticatedDecryptionFilter

        // The StringSource dtor will be called immediately
        //  after construction below. This will cause the
        //  destruction of objects it owns. To stop the
        //  behavior so we can get the decoding result from
        //  the DecryptionFilter, we must use a redirector
        //  or manually Put(...) into the filter without
        //  using a StringSource.
        StringSource ss2( cipher, true,
            new Redirector( df /*, PASS_EVERYTHING */ )
        ); // StringSource

        // If the object does not throw, here's the only
        //  opportunity to check the data's integrity
        if( true == df.GetLastResult() ) {
            cout << "recovered text: " << rpdata << endl;
        }
    }
    catch( CryptoPP::Exception& e )
    {
        cerr << e.what() << endl;
        exit(1);
    }

    return 0;
}
#endif
