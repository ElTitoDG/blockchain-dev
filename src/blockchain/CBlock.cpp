#include "CBlock.hpp"
#include <stdio.h>
#include <string.h>
#include <unistd.h>


using namespace blockchain;

CBlock::CBlock(CBlock* prevBlock)
{
    mPrevBlock = prevBlock;

    memset(mHash, CryptoPP::SHA256::DIGESTSIZE, 0);
    if (mPrevBlock)
        memcpy(mPrevBlock, mPrevBlock->getHash(), CryptoPP::SHA256::DIGESTSIZE);                                        // Copia el hash del bloque previo al objeto actual del hash del bloque previo
    else
        memset(mPrevHash, CryptoPP::SHA256::DIGESTSIZE, 0);                                                             // mPrevHash a Nulo
    
    mCratedTS = time(0);                                                                                        // mCreatedTS a tiempo del momento
    mNonce = 0;
    mDataSize = 0;
    mData = 0;
    calculateHash();
}

void CBlock::calculateHash()
{
                  // tamaño mPrevHash                     tamaño mCreatedTS  tamaño mData   tamaño mNonce
    uint32_t sz = (CryptoPP::SHA256::DIGESTSIZE + sizeof(time_t) + mDataSize + sizeof(uint32_t));
    uint8_t* buf = new uint8_t[sz];                                                                             // Generamos un puntero ha ese tamaño definido
    uint8_t* ptr = buf;                                                                                         // Ponemos el cursor al principio

    memcpy(ptr, mPrevHash, CryptoPP::SHA256::DIGESTSIZE * sizeof(uint8_t));
    ptr += CryptoPP::SHA256::DIGESTSIZE * sizeof(uint8_t);

    memcpy(ptr, &mCratedTS, sizeof(time_t));
    ptr += sizeof(time_t);

    if (mDataSize != 0)
    {
        memcpy(ptr, mData, mDataSize);
        ptr += mDataSize;
    }
    memcpy(ptr, &mNonce, sizeof(uint32_t));
    ptr += sizeof(uint32_t);

    // Crypto++ hashing
    CryptoPP::SHA256 hash;
    hash.Update(buf, sz);
    hash.Final(mHash);

    delete[] buf;
}

/* uint8_t* CBlock::getHash()
{
    return mHash;
} */

// Formato hexadecimal del Hash
std::string CBlock::getHashStr()
{
    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach(new CryptoPP::StringSink(output));

    encoder.Put(mHash, sizeof(mHash));
    encoder.MessageEnd();

    return output;
}


/* // Devuelve el puntero del bloque anterior
CBlock* CBlock::getPrevBlock()
{
    return mPrevBlock;
} */


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
        usleep(10); // usleep is in microseconds
    }
}

/* uint32_t CBlock::getNonce()
{
    return mNonce;
} */