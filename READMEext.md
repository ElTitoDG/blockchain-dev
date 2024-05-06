# Blockchain en C++ utilizando Crypto++ y CMake

Este proyecto implementa una blockchain simple en C++, utilizando la librería [Crypto++](https://cryptopp.com/) para el cálculo de hashes y la generación de claves criptográficas. La estructura del proyecto sigue el paradigma de programación orientada a objetos (OOP) y consta de dos clases principales: `CBlock` y `CChain`.

## Tabla de contenidos

* [Clase CBlock](#clase-cblock)
* [Clase CChain](#clase-cchain)
* [Programa principal (main)](#programa-principal-main)
* [CMakeLists.txt](#cmakeliststxt)
* [Conclusión](#conclusión)

## Clase CBlock

La clase `CBlock` representa un bloque en la blockchain. Los bloques son los componentes básicos de la blockchain y contienen información como el índice del bloque, un nonce (número utilizado una sola vez), una marca de tiempo, datos, el hash del bloque actual y el hash del bloque anterior.

### Atributos

* **`imdex`** (entero): El índice del bloque en la blockchain.
* **`nonce`** (entero): Un número utilizado una sola vez que se usa en el proceso de minería.
* **`timestamp`** (std::chrono::system_clock::time_point): La marca de tiempo que indica cuando se creó el bloque.
* **`data`** (std::string): Los datos almacenados en el bloque (por ejemplo, información de transacciones).
* **`hash`** (std::string): El hash del bloque actual, calculado a partir de los datos del bloque.
* **`prevHash`** (std::string): El hash del bloque anterior en la blockchain.

### Métodos

* **`CBlock(int index, const std::string &data, const std::string &prevHash)`**: Constructor de la clase que inicializa el índice, los datos, el hash del bloque anterior y establece el nonce en 0. También calcula el hash del bloque actual utilizando el método calculateHash().
* **`std::string calculateHash() const`**: Método que calcula el hash del bloque actual utilizando el algoritmo SHA-256 de la librería Crypto++. El hash se genera a partir de la concatenación del índice, los datos y el hash del bloque anterior.
* **`void mineBlock(int difficulty)`**: Método que simula el proceso de minería ajustando el nonce hasta que se encuentre un hash válido según la dificultad especificada. Un hash es válido si tiene un número determinado de ceros al principio, donde el número de ceros depende de la dificultad.

### Archivo de encabezado (CBlock.hpp)

```cpp
#ifndef C_BLOCK_INCLUDED_
#define C_BLOCK_INCLUDED_

#include <chrono>
#include <cryptopp/config.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <sstream>
#include <string>

namespace blockchain 
{
    class CBlock
    {        
        private:
            int index;  
            int nonce;
            std::chrono::system_clock::time_point timestamp;
            std::string data;
        
        public:
            std::string hash;
            std::string prevHash;
            // int hashNum;
            
            CBlock(int index, const std::string &data, const std::string &prevHash);
            std::string calculateHash() const;
            void mineBlock(int difficulty);
    };
}  // namespace blockchain

#endif  // C_BLOCK_INCLUDED_
```
### Archivo de implementación (CBlock.cpp)
 ```cpp
 #include "CBlock.hpp"

using namespace blockchain;

CBlock::CBlock(int index, const std::string &data, const std::string &prevHash)
    : index(index), data(data), prevHash(prevHash), nonce(0)
{
    timestamp = std::chrono::system_clock::now();
    hash = calculateHash();
}

std::string CBlock::calculateHash() const
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

    return result;
}

void CBlock::mineBlock(int difficulty)
{
  std::string target(difficulty, '0');
  while (hash.substr(0, difficulty) != target) 
  {
      nonce++;
      hash = calculateHash();
  }
  std::cout << "Block mined: " << hash << std::endl;
}
 ```

## Clase CChain
La clase **`CChain`** representa la blockchain en sí. Contiene un vector de bloques y la dificultad de minería. 
La clase proporciona métodos para crear un bloque génesis, agregar un nuevo bloque 
a la cadena y verificar la integridad de la blockchain.

### Atributos


* **`chain`** (std::vector<CBlock>): Un vector que almacena los bloques de la blockchain.
* **`mDifficulty`** (entero): La dificultad de minería, que determina cuán difícil es encontrar un hash válido para un bloque.

### Métodos


* **`CChain(int difficulty)`**: Constructor de la clase que inicializa la dificultad de minería y crea un bloque génesis utilizando el método createGenesisBlock().
* **`static CBlock createGenesisBlock()`**: Método estático que crea y devuelve un bloque génesis con índice 0, datos "Genesis Block" y hash del bloque anterior establecido en "0".
* **`void addBlock(const std::string &data)`**: Método que agrega un nuevo bloque a la blockchain con los datos proporcionados. Este método crea un nuevo bloque, mina el bloque utilizando el método mineBlock() de la clase CBlock y luego lo agrega a la cadena de bloques.
* **`bool isValid() const`**: Método que verifica la integridad de la blockchain comparando los hashes de cada bloque y el hash del bloque anterior. Si todos los hashes son válidos y coinciden con los hashes calculados, la blockchain es válida; de lo contrario, es inválida.


### Archivo de encabezado (CChain.hpp)
```cpp
#ifndef C_CHAIN_INCLUDE_
#define C_CHAIN_INCLUDE_

#include "CBlock.hpp"
#include <vector>

namespace blockchain
{
    class CChain
    {        
         private:
            std::vector<CBlock> chain;  // Lista de bloques
            int mDifficulty;            // Dificultad
        
         public:
            explicit CChain(int difficulty);  // Constructor
            static CBlock createGenesisBlock() { return CBlock(0, "Genesis Block", "0"); }
            void addBlock(const std::string &data);
            bool isValid() const;
    };
}  // namespace blockchain

#endif  // C_CHAIN_INCLUDE_
```

### Archivo de implementación (CChain.cpp)
```cpp
#include "CChain.hpp"

using namespace blockchain;

CChain::CChain(int difficulty) : mDifficulty(difficulty) 
{
    chain.push_back(createGenesisBlock());
}

void CChain::addBlock(const std::string &data) 
{
    CBlock newBlock(chain.size(), data, chain.back().hash);
    std::cout << "Mining block... " << std::endl;
    newBlock.mineBlock(mDifficulty);
    chain.push_back(newBlock);
}

bool CChain::isValid() const 
{
    for (size_t i = 1; i < chain.size(); i++) 
    {
        const CBlock &currentBlock = chain[i];
        const CBlock &prevBlock = chain[i - 1];

        if (currentBlock.hash != currentBlock.calculateHash())
            return false;
        if (currentBlock.prevHash != prevBlock.hash)
            return false;
    }
    return true;
}
```

## Programa principal (main)

El archivo **`main.cpp`** contiene la función principal que crea una instancia de **`CChain`** y agrega algunos bloques con datos de ejemplo. 
Luego, verifica la validez de la blockchain y muestra un mensaje en consecuencia.
```cpp
#include "blockchain/CChain.hpp"
#include <iostream>

using namespace std;
using namespace blockchain;

int main() 
{
    CChain blockchain(0);

    blockchain.addBlock("This is the first block");
    blockchain.addBlock("This is the second block");
    blockchain.addBlock("This is the third block");

    if (blockchain.isValid())
        std::cout << "Blockchain is valid" << std::endl;
    else
        std::cout << "Blockchain is not valid" << std::endl;
    
    return 0;
}
```

## CMakeLists.txt
El archivo **`CMakeLists.txt`** se utiliza para configurar el proyecto con CMake. Establece el nombre del proyecto, incluye los directorios de encabezados necesarios, 
especifica los archivos fuente y crea un ejecutable vinculado con la librería Crypto++.
```cmake
cmake_minimum_required(VERSION 3.20)

# Declaramos la variable del nombre del projecto
set(PROJECT_NAME "blockchain-dev")
set(CRYPTOPP_INCLUDE_DIR "~/Documents/Dev/blockchain-dev/include")

# Declaramos el nombre del projecto
project(${PROJECT_NAME})

include_directories(${CRYPTOPP_INCLUDE_DIR})
FILE(GLOB SRCS "${CMAKE_CURRENT_LIST_DIR}/src/blockchain/*.cpp"
                "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} cryptopp)  # pthread
```
## Conclusión

Este proyecto implementa una blockchain simple en C++ utilizando la librería Crypto++ para el 
cálculo de hashes y la generación de claves criptográficas. La estructura del proyecto sigue el 
paradigma de programación orientada a objetos (OOP) y consta de dos clases principales: 
**`CBlock`** y **`CChain`**. La clase **`CBlock`** representa un bloque en la blockchain, mientras que la 
clase **`CChain`** representa la blockchain completa y proporciona métodos para agregar bloques 
y verificar su integridad. Este enfoque OOP facilita la extensión y mantenibilidad del código, al 
tiempo que permite una mejor separación de responsabilidades entre los componentes del proyecto.

