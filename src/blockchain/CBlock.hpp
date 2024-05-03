#ifndef __C_BLOCK_INCLUDED__
#define __C_BLOCK_INCLUDED__

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <cryptopp/config.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

namespace blockchain 
{
    class CBlock
    {
        private:
            int index;
            std::chrono::system_clock::time_point timestamp;
            std::string data;
            std::string prevHash;
            std::string hash;

        public:
            CBlock(int index, const std::string &data, const std::string& prevHash);
            std::string calculateHash();
    };
}

#endif // __C_BLOCK_INCLUDED__
