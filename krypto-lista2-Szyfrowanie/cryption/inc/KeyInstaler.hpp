#ifndef KEYINSTALER_H
#define KEYINSTALER_H
#include <string>
#include <iostream>
#include <fstream>
#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>



namespace CONST {
constexpr byte initialVectorByte[CryptoPP::AES::DEFAULT_KEYLENGTH] =
    { 0xB1, 0x27, 0x11, 0x1F, 0x7D, 0xA5, 0x3D, 0x21, 0x60, 0x97, 0x33, 0x4F, 0xB8, 0xA7, 0xD6, 0x85};
}

class KeyInstaler
{
public:
    KeyInstaler(std::ostream& outFile,
                std::istream& inStream = std::cin,
                std::shared_ptr<CryptoPP::RandomNumberGenerator> random = std::make_shared<CryptoPP::AutoSeededRandomPool>())
        : out(outFile), in(inStream), random(random){}

    void install();
private:
    std::ostream& out;
    std::istream& in;
    std::shared_ptr<CryptoPP::RandomNumberGenerator> random;
};

#endif // KEYINSTALER_H
