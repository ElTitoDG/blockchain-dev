#ifndef C_BLOCK_INCLUDED_
#define C_BLOCK_INCLUDED_

#include <chrono>
#include <cryptopp/config.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <sstream>
#include <string>

namespace blockchain
{
class CBlock
{
  private:
    int index;
    int nonce;
    std::chrono::system_clock::time_point timestamp;
    std::string data;

  public:
    std::string hash;
    std::string prevHash;
    int hashNum;
    CBlock(int index, const std::string &data, const std::string &prevHash);
    std::string calculateHash(int number) const;
    void mineBlock(int difficulty);
};
} // namespace blockchain

#endif // C_BLOCK_INCLUDED_
