#ifndef CRYPTIONMAIN_H
#define CRYPTIONMAIN_H
#include <iostream>

class CryptionMain
{
public:
    CryptionMain(std::istream& in = std::cin, std::ostream& out = std::cout)
        : in(in),
          out(out) {}

    int install();
    int run(int numOfArg, char* args[]);

    static void hideStdinKeystrokes();
    static void showStdinKeystrokes();

private:
    void showHelp(char* filename);

    std::istream& in;
    std::ostream& out;
};

#endif // CRYPTIONMAIN_H
