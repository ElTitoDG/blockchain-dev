#ifndef C_BLOCK_INCLUDED_
#define C_BLOCK_INCLUDED_

#include <chrono>
#include <cryptopp/config.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <sstream>
#include <string>

class CBlock
{
  private:
    int index;
    int nonce;
    std::chrono::system_clock::time_point timestamp;
    std::string data;

    static std::string addZeros(std::string str, int num) ;

  public:
    std::string hash;
    std::string prevHash;
    // int hashNum;
    CBlock(int index, const std::string &data, const std::string &prevHash);
    std::string calculateHash(int difficulty) const;
    void mineBlock(int difficulty);
};

#endif // C_BLOCK_INCLUDED_
