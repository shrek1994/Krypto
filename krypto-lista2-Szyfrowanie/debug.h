#pragma once

constexpr bool debug = false;


inline void printHex(const std::string& tab)
{
    printHex(tab.c_str());
}

inline void printHex(const char* tab)
{
    if (debug)
    {
        printf("HEX: ");
        for(int i=0;*(tab+i)!=0x00;i++)
            printf("0x%X, ",(unsigned char)*(tab+i));
        printf("\n");
    }
}

#define LOG \
    if (debug) std::cout << __FILE__ << ":" << __LINE__ << ": "

