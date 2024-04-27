#include "blockchain/CChain.hpp"
#include <iostream>

using namespace std;
using namespace blockchain;

int main(int argc, char **argv)
{
    cout << "Start" << endl;

    CChain chain(1);
    cout << "Cadena empezada" << endl;

    CBlock* genesis = chain.getCurrentBlock();

    uint8_t* garbage = new uint8_t[32];
    for (uint32_t i = 0; i < 32; i++)
        garbage[i] = time(0) % 255;

    cout << "Contenido basura generado" << endl;

    chain.appendToCurrentBlock(garbage, 32);
    delete[] garbage;

    cout << "Datos añadidos al bloque" << endl;

    chain.nextBlock();

    cout << "Siguiente bloque minado" << endl;

    cout << "Hash del Genesis: " << chain.getCurrentBlock()->getPrevBlock()->getHashStr() 
                                 << endl << "Nonce: " <<  chain.getCurrentBlock()->getNonce() << endl;

    garbage = new uint8_t[32];
    for (uint32_t i = 0; i < 32; i++)
        garbage[i] = time(0) % 255;

    cout << "Contenido basura generado" << endl;

    chain.appendToCurrentBlock(garbage, 32);
    delete[] garbage;

    cout << "Datos añadidos al bloque" << endl;

    chain.nextBlock();

    cout << "Siguiente bloque minado" << endl;

    cout << "Hash del bloque previo: " << chain.getCurrentBlock()->getPrevBlock()->getHashStr() 
                                 << endl << "Nonce: " <<  chain.getCurrentBlock()->getNonce() << endl;

    return 0;

}
