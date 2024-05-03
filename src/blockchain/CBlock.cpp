#include "CBlock.hpp"

using namespace blockchain;

CBlock::CBlock(int index, const std::string &data, const std::string &prevHash) : index(index), data(data), prevHash(prevHash)
{
    timestamp = std::chrono::system_clock::now();
    hash = calculateHash();
}

std::string CBlock::calculateHash()
{
    std::stringstream ss;
    ss << index << data << prevHash;
    std::string str = ss.str();

    std::time_t tt = std::chrono::system_clock::to_time_t(timestamp);
    std::cout << "Timestamp: " << std::ctime(&tt);

    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    hash.CalculateDigest(digest, (CryptoPP::byte*)str.c_str(), str.length());

    std::string result;
    CryptoPP::HexEncoder encoder;
    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return result;
}
