#include "CBlock.hpp"
#include <stdio.h>
#include <string.h>
#include <unistd.h>


using namespace blockchain;

CBlock::CBlock(CBlock* prevBlock)
{
    mPrevBlock = prevBlock;

    memset(mHash, SHA256_DIGEST_LENGTH, 0);
    if (mPrevBlock)
        memcpy(mPrevBlock, mPrevBlock->getHash(), SHA256_DIGEST_LENGTH);                                        // Copia el hash del bloque previo al objeto actual del hash del bloque previo
    else
        memset(mPrevHash, SHA256_DIGEST_LENGTH, 0);                                                             // mPrevHash a Nulo
    
    mCratedTS = time(0);                                                                                        // mCreatedTS a tiempo del momento
    mNonce = 0;
    mDataSize = 0;
    mData = 0;
    calculateHash();
}

void CBlock::calculateHash()
{
                  // tamaño mPrevHash                     tamaño mCreatedTS  tamaño mData   tamaño mNonce
    uint32_t sz = (SHA256_DIGEST_LENGTH + sizeof(time_t) + mDataSize + sizeof(uint32_t));
    uint8_t* buf = new uint8_t[sz];                                                                             // Generamos un puntero ha ese tamaño definido
    uint8_t* ptr = buf;                                                                                         // Ponemos el cursor al principio

    memcpy(ptr, mPrevHash, SHA256_DIGEST_LENGTH * sizeof(uint8_t));
    ptr += SHA256_DIGEST_LENGTH * sizeof(uint8_t);

    memcpy(ptr, &mCratedTS, sizeof(time_t));
    ptr += sizeof(time_t);

    if (mDataSize != 0)
    {
        memcpy(ptr, mData, mDataSize);
        ptr += mDataSize;
    }
    memcpy(ptr, &mNonce, sizeof(uint32_t));
    ptr += sizeof(uint32_t);

    // libssl hashing
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, buf, sz);
    SHA256_Final(mHash, &sha256);

    delete[] buf;
}

uint8_t* CBlock::getHash()
{
    return mHash;
}

// Formato hexadecimal del Hash
std::string CBlock::getHashStr()
{
    char buf[SHA256_DIGEST_LENGTH * 2 + 1];
    for (uint32_t i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(buf + (i * 2), "%02x", mHash[i]);
    }
        
    buf[SHA256_DIGEST_LENGTH * 2] = 0;
    return std::string(buf);
    
}


// Devuelve el puntero del bloque anterior
CBlock* CBlock::getPrevBlock()
{
    return mPrevBlock;
}


void CBlock::appendData(uint8_t* data, uint32_t size)
{
    uint8_t* newData = new uint8_t[mDataSize + size];
    uint8_t* ptr = newData;

    if (mDataSize != 0)
    {
        memcpy(ptr, mData, mDataSize);
        ptr += mDataSize;
        delete[] mData;
    }

    memcpy(ptr, data, size);
    mData = newData;
    mDataSize += size;
}

bool CBlock::isDifficulty(int difficulty)
{
    for (uint32_t i = 0; i < difficulty; i++)
    {
        if (mHash[i] != 0)
            return false;
    }
    return true;
}

void CBlock::mine(int difficulty)
{
    while (!isDifficulty(difficulty))
    {
        mNonce++;
        calculateHash();
        usleep(10);
    }
}

uint32_t CBlock::getNonce()
{
    return mNonce;
}