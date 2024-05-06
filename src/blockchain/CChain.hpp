#ifndef C_CHAIN_INCLUDE_
#define C_CHAIN_INCLUDE_

#include "CBlock.hpp"
#include <vector>

class CChain
{
  private:
    std::vector<CBlock> chain;  // Lista de bloques
    int mDifficulty;            // Dificultad

  public:
    explicit CChain(int difficulty) : mDifficulty(difficulty) { chain.push_back(createGenesisBlock()); }; // Constructor
    static CBlock createGenesisBlock() { return CBlock(0, "Genesis Block", "0"); }
    void addBlock(const std::string &data);
    bool isValid() const;
};

#endif // C_CHAIN_INCLUDE_