#include "CBlock.hpp"
#include <stdio.h>
#include <string.h>

using namespace blockchain;

CBlock::CBlock(CBlock* prevBlock)
{
    mPrevBlock = prevBlock;

    memset(mHash, SHA256_DIGEST_LENGTH, 0);
    if (mPrevBlock)
        memcpy(mPrevBlock, mPrevBlock->getHash(), SHA256_DIGEST_LENGTH);                                        // Copia el hash del bloque previo al objeto actual del hash del bloque previo
    else
        memset(mPrevHash, SHA256_DIGEST_LENGTH, 0);                                                             // mPrevHash a Nulo
    
    mCratedTS = time(0);
    mNonce = 0;
    mDataSize = 0;
    mData = 0;
    calculateHash();
}

void CBlock::calculateHash()
{
    uint32_t sz = (SHA256_DIGEST_LENGTH * sizeof(uint8_t) + sizeof(time_t) + mDataSize + sizeof(uint32_t));
    uint8_t* buf = new uint8_t[sz];
    uint8_t* ptr = buf;

    memcpy(ptr, mPrevHash, SHA256_DIGEST_LENGTH * sizeof(uint8_t));
    ptr += 20 * sizeof(time_t);

    memcpy(ptr, &mCratedTS, sizeof(time_t));
    ptr += sizeof(time_t);

    if (mDataSize != 0)
    {
        memcpy(ptr, mData, mDataSize);
        ptr += mDataSize;
    }

}