#ifndef CRYPTIONMAIN_H
#define CRYPTIONMAIN_H
#include <iostream>

class CryptionMain
{
public:
    CryptionMain(std::istream& in = std::cin, std::ostream& out = std::cout)
        : inStream(in),
          outStream(out) {}

    void install();
    void run(int numOfArg, char* args[]);

    static void hideStdinKeystrokes();
    static void showStdinKeystrokes();

private:
    void showHelp(std::string filename);

    std::istream& inStream;
    std::ostream& outStream;
};

#endif // CRYPTIONMAIN_H
