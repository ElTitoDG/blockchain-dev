#include "blockchain/CChain.hpp"
#include <iostream>

using namespace std;

int main()
{

    CChain blockchain(2);

    blockchain.addBlock("This is the first block");
    blockchain.addBlock("This is the second block");
    blockchain.addBlock("This is the third block");

    if (blockchain.isValid())
        std::cout << "Blockchain is valid" << std::endl;
    else
        std::cout << "Blockchain is not valid" << std::endl;

    return 0;
}
