#include "CBlock.hpp"

using namespace blockchain;

CBlock::CBlock(int index, const std::string &data, const std::string &prevHash)
    : index(index), data(data), prevHash(prevHash), nonce(0)
{
    timestamp = std::chrono::system_clock::now();
    hash = calculateHash(1);
}

std::string CBlock::calculateHash(int number) const
{
    std::stringstream ss;
    ss << index << data << prevHash << number;
    std::string str = ss.str();

    CryptoPP::SHA256 mhash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    mhash.CalculateDigest(digest, (CryptoPP::byte *)str.c_str(), str.length());

    std::string result;
    CryptoPP::HexEncoder encoder;
    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return result;
}

void CBlock::mineBlock(int difficulty)
{
    std::string target(difficulty, '0');
    int number = 0;
    while (hash.substr(0, difficulty) != target)
    {
        number++;
        nonce++;
        hash = calculateHash(number);
    }
    std::cout << "Block mined: " << hash << " with number: " << number << std::endl;
}
