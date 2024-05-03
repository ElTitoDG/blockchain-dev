#ifndef C_CHAIN_INCLUDE_
#define C_CHAIN_INCLUDE_

#include "CBlock.hpp"
#include <vector>

namespace blockchain
{
class CChain
{
  private:
    std::vector<CBlock> chain; // Lista de bloques
    int mDifficulty;            // Dificultad

  public:
    explicit CChain(int difficulty); // Constructor
    static CBlock createGenesisBlock() { return CBlock(0, "Genesis Block", "0"); }
    void addBlock(const std::string &data);
    bool isValid() const;
};
} // namespace blockchain

#endif // C_CHAIN_INCLUDE_