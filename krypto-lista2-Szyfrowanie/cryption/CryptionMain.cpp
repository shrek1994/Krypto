#include "CryptionMain.hpp"
#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <fstream>

#include <termios.h>
#include <unistd.h>

#include "CryptionFactory.hpp"
#include "KeyInstaler.hpp"

namespace {
const byte keyByte[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x90 };
const byte ivByte[CryptoPP::AES::DEFAULT_KEYLENGTH] = { 0x98, 0x76, 0x54, 0x32, 0x10 };

CryptoPP::SecByteBlock key = {keyByte, sizeof(keyByte)};
CryptoPP::SecByteBlock iv =  {ivByte, sizeof(ivByte)};
} //namespace

void CryptionMain::install()
{
    std::string filename;

    std::cout << "Podaj nazwe keystore'a: " << std::flush;
    std::cin >> filename;

    std::fstream file;
    file.open(filename);

    KeyInstaler installer(file);
    installer.install();

    file.close();
}

void CryptionMain::run(int numOfArg, char *args[])
{
    if ( numOfArg < 5)
    {
        showHelp(args[0]);
        return;
    }

    std::string modeOfCryption = args[1];
    std::string pathToKeyStore = args[2];
    std::string idKey = args[3];
    std::string fileName = args[4];

    CryptionFactory factory(modeOfCryption);
    auto cryption = factory.create(key, iv);

    std::cout<< "Encrypt(e) czy Decrypt(d) : "<< std::flush;
    char mode;
    std::cin >> mode;

    std::ifstream inFile(fileName);
    if (mode =='d')
    {
        auto out = cryption->decrypt(inFile);
        std::ofstream outFile(fileName + ".aes");
//        std::cout << out.str();
        outFile << out.str();
        outFile.close();
    }
    else
    {
        std::ifstream inFile(fileName);
        auto out = cryption->encrypt(inFile);
        std::ofstream outFile(fileName + ".txt");
//        std::cout << out.str();
        outFile << out.str();
        outFile.close();
    }
}



void CryptionMain::hideStdinKeystrokes()
{
    termios tty;

    tcgetattr(STDIN_FILENO, &tty);

    /* we want to disable echo */
    tty.c_lflag &= ~ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void CryptionMain::showStdinKeystrokes()
{
    termios tty;

    tcgetattr(STDIN_FILENO, &tty);

    /* we want to reenable echo */
    tty.c_lflag |= ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void CryptionMain::showHelp(char* filename)
{
    out << filename << "TRYBSZYFROWANIA SCIEZKADOKEYSTORE'A IDKLUCZA PLIKDOZASZYFROWANIA\n"
        << "np: " << filename << "AES CBC keystore.aes ID plik.txt\n";
}

