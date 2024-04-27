#ifndef __C_CHAIN_INCLUDE__
#define __C_CHAIN_INCLUDE__

#include "CBlock.hpp"
#include <vector>

namespace blockchain
{
    class CChain
    {
        private:
            std::vector<CBlock> mChain;                                 // Lista de bloques
            CBlock* mCurrentBlock;                                      // Puntero al bloque actual
            int mDifficulty;                                            // Dificultad

        public:
            CChain(int difficulty);                                     // Constructor
            void appendToCurrentBlock(uint8_t* data, uint32_t size);    // 
            void nextBlock();                                           // Continua al siguiente bloque
            CBlock* getCurrentBlock() { return mCurrentBlock; }                                // Saca un puntero al bloque actual
    };
}


#endif // __C_CHAIN_INCLUDE__