# Blockchain en C++ utilizando Crypto++ y CMake

Este proyecto implementa una blockchain simple en C++, utilizando la librería [Crypto++](https://cryptopp.com/) para
el cálculo de hashes y la generación de claves criptográficas. La estructura del proyecto sigue el paradigma de
programación orientada a objetos (OOP) y consta de dos clases principales: `CBlock` y `CChain`.

## Tabla de contenidos

* [Clase CBlock](#clase-cblock)
* [Clase CChain](#clase-cchain)
* [Programa principal (main)](#programa-principal-main)
* [CMakeLists.txt](#cmakeliststxt)
* [Conclusión](#conclusión)

## Clase CBlock

La clase **`CBlock`** representa un bloque en la blockchain. Los bloques son los componentes básicos de la blockchain y
contienen información como el índice del bloque, un nonce (número utilizado una sola vez), una marca de tiempo,
datos, el hash del bloque actual y el hash del bloque anterior.

### Atributos

* **`imdex`** (entero): El índice del bloque en la blockchain.
* **`nonce`** (entero): Un número utilizado una sola vez que se usa en el proceso de minería.
* **`timestamp`** (std::chrono::system_clock::time_point): La marca de tiempo que indica cuando se creó el bloque.
* **`data`** (std::string): Los datos almacenados en el bloque (por ejemplo, información de transacciones).
* **`hash`** (std::string): El hash del bloque actual, calculado a partir de los datos del bloque.
* **`prevHash`** (std::string): El hash del bloque anterior en la blockchain.

### Métodos

* **`CBlock(int index, const std::string &data, const std::string &prevHash)`**: Constructor de la clase que inicializa
  el índice, los datos, el hash del bloque anterior y establece el nonce en 0. También calcula el hash del bloque
  actual utilizando el método calculateHash().
* **`std::string calculateHash() const`**: Método que calcula el hash del bloque actual utilizando el algoritmo
  SHA-256 de la librería Crypto++. El hash se genera a partir de la concatenación del índice, los datos y el hash
  del bloque anterior.
* **`void mineBlock(int difficulty)`**: Método que simula el proceso de minería ajustando el nonce hasta que se
  encuentre un hash válido según la dificultad especificada. Un hash es válido si tiene un número determinado de ceros
  al principio, donde el número de ceros depende de la dificultad.

## Clase CChain

La clase **`CChain`** representa la blockchain en sí. Contiene un vector de bloques y la dificultad de minería.
La clase proporciona métodos para crear un bloque génesis, agregar un nuevo bloque
a la cadena y verificar la integridad de la blockchain.

### Atributos

* **`chain`** (std::vector<CBlock>): Un vector que almacena los bloques de la blockchain.
* **`mDifficulty`** (entero): La dificultad de minería, que determina cuán difícil es encontrar un hash válido para un bloque.

### Métodos

* **`CChain(int difficulty)`**: Constructor de la clase que inicializa la dificultad de minería y crea un bloque génesis
  utilizando el método createGenesisBlock().
* **`static CBlock createGenesisBlock()`**: Método estático que crea y devuelve un bloque génesis con índice 0,
  datos "Genesis Block" y hash del bloque anterior establecido en "0".
* **`void addBlock(const std::string &data)`**: Método que agrega un nuevo bloque a la blockchain con los datos
  proporcionados. Este método crea un nuevo bloque, mina el bloque utilizando el método mineBlock() de la clase
  **`CBlock`** y luego lo agrega a la cadena de bloques.
* **`bool isValid() const`**: Método que verifica la integridad de la blockchain comparando los hashes de cada bloque
  y el hash del bloque anterior. Si todos los hashes son válidos y coinciden con los hashes calculados,
  la blockchain es válida; de lo contrario, es inválida.

## Programa principal (main)

El archivo **`main.cpp`** contiene la función principal que crea una instancia de **`CChain`** y agrega algunos bloques
con datos de ejemplo. Luego, verifica la validez de la blockchain y muestra un mensaje en consecuencia.

## CMakeLists.txt
El archivo **`CMakeLists.txt`** se utiliza para configurar el proyecto con CMake. Establece el nombre del proyecto,
incluye los directorios de encabezados necesarios, especifica los archivos fuente y crea un ejecutable vinculado
con la librería Crypto++.

## Conclusión

Este proyecto implementa una blockchain simple en C++ utilizando la librería Crypto++ para el
cálculo de hashes y la generación de claves criptográficas. La estructura del proyecto sigue el
paradigma de programación orientada a objetos (OOP) y consta de dos clases principales:
**`CBlock`** y **`CChain`**. La clase **`CBlock`** representa un bloque en la blockchain, mientras que la
clase **`CChain`** representa la blockchain completa y proporciona métodos para agregar bloques
y verificar su integridad. Este enfoque OOP facilita la extensión y mantenibilidad del código, al
tiempo que permite una mejor separación de responsabilidades entre los componentes del proyecto.

