#include "CBlock.hpp"

CBlock::CBlock(int index, const std::string &data, const std::string &prevHash)
    : index(index), data(data), prevHash(prevHash), nonce(0)
{
    timestamp = std::chrono::system_clock::now();
    hash = calculateHash(2);
}

std::string CBlock::calculateHash(int difficulty) const
{
    std::stringstream ss;
    ss << index << data << prevHash;
    std::string str = ss.str();

    CryptoPP::SHA256 mhash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    mhash.CalculateDigest(digest, (CryptoPP::byte *)str.c_str(), str.length());

    std::string result;
    CryptoPP::HexEncoder encoder;
    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
    result = addZeros(result, difficulty);

    return result;
}

void CBlock::mineBlock(int difficulty)
{
    std::string target(difficulty, '0');
    while (hash.substr(0, difficulty) != target) {
        nonce++;
        hash = calculateHash(2);
    }
    std::cout << "Block mined: " << hash << std::endl;
}


std::string CBlock::addZeros(std::string str, int num) {
    // Asegurarnos de que el número de ceros no supere la longitud de la cadena
    num = std::min(num, static_cast<int>(str.length()));

    // Revertir la cadena
    std::reverse(str.begin(), str.end());

    // Insertar los ceros al principio (ahora al final debido a la reversión)
    for(int i = 0; i < num; i++) {
        str += '0';
    }

    // Revertir la cadena de nuevo
    std::reverse(str.begin(), str.end());

    return str;
}