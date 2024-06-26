#include "CChain.hpp"

void CChain::addBlock(const std::string &data)
{
    CBlock newBlock(chain.size(), data, chain.back().hash);
    std::cout << "Mining block... " << std::endl;
    newBlock.mineBlock(mDifficulty);
    chain.push_back(newBlock);
}

bool CChain::isValid() const
{
    for (size_t i = 1; i < chain.size(); i++)
    {
        const CBlock &currentBlock = chain[i];
        const CBlock &prevBlock = chain[i - 1];

        if (currentBlock.hash != currentBlock.calculateHash(2))
            return false;
        if (currentBlock.prevHash != prevBlock.hash)
            return false;
    }
    return true;
}