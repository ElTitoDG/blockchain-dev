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

## Clase CChain
La clase **`CChain`** representa la blockchain en sí. Contiene un vector de bloques y la dificultad de minería. 
La clase proporciona métodos para crear un bloque génesis, agregar un nuevo bloque 
a la cadena y verificar la integridad de la blockchain.


## Programa principal (main)

El archivo **`main.cpp`** contiene la función principal que crea una instancia de **`CChain`** y agrega algunos bloques con datos de ejemplo. 
Luego, verifica la validez de la blockchain y muestra un mensaje en consecuencia.


## CMakeLists.txt
El archivo **`CMakeLists.txt`** se utiliza para configurar el proyecto con CMake. Establece el nombre del proyecto, incluye los directorios de encabezados necesarios, 
especifica los archivos fuente y crea un ejecutable vinculado con la librería Crypto++.

## Conclusión

Este proyecto implementa una blockchain simple en C++ utilizando la librería Crypto++ para el 
cálculo de hashes y la generación de claves criptográficas. La estructura del proyecto sigue el 
paradigma de programación orientada a objetos (OOP) y consta de dos clases principales: 
**`CBlock`** y **`CChain`**. La clase **`CBlock`** representa un bloque en la blockchain, mientras que la 
clase **`CChain`** representa la blockchain completa y proporciona métodos para agregar bloques 
y verificar su integridad. Este enfoque OOP facilita la extensión y mantenibilidad del código, al 
tiempo que permite una mejor separación de responsabilidades entre los componentes del proyecto.

