#ifndef __C_BLOCK_INCLUDED__
#define __C_BLOCK_INCLUDED__

#include <openssl/sha.h>
#include <string>

namespace blockchain 
{
    class CBlock
    {
        private:
            uint8_t mHash[SHA256_DIGEST_LENGTH];                // Hash actual
            uint8_t mPrevHash[SHA256_DIGEST_LENGTH];            // Hash previo
            CBlock* mPrevBlock;                                 // Puntero al bloque anterior, sera nulo
            uint8_t* mData;                                     // Byte de datos de la transacción
            uint32_t mDataSize;                                 // Tamaño de los datos
            time_t mCratedTS;                                   // Timestamp de la creación del bloque
            uint32_t mNonce;                                    // Nonce del bloque

        public:
            CBlock(CBlock* prevBlock);                          // Constructor
            void calculateHash();                               // Calcula el hash en sha256
            uint8_t* getHash();                                 // Saca el hash actual -> mHash
            std::string getHashStr();                           // Saca la representacion de mHash en string
            CBlock* getPrevBlock();                             // Recibe el puntero del bloque anterior 
            void appendData(uint8_t* data, uint32_t size);      // Añade datos a mData
            bool isDifficulty(int difficulty);                  // Dificultad
            void mine(int difficulty);                          // Mina un bloque
            uint32_t getNonce();                                // Consigue el valor Nonce
    };
}

#endif // __C_BLOCK_INCLUDED__
