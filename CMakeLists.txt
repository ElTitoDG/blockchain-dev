cmake_minimum_required(VERSION 3.20)

# Declaramos la variable del nombre del projecto
set(PROJECT_NAME "blockchain-dev")
set(CRYPTOPP_INCLUDE_DIR "~/Documents/Dev/blockchain-dev/include")

# Declaramos el nombre del projecto
project(${PROJECT_NAME})

include_directories(${CRYPTOPP_INCLUDE_DIR})
FILE(GLOB SRCS "${CMAKE_CURRENT_LIST_DIR}/src/blockchain/*.cpp"
                "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

                # "${CMAKE_CURRENT_LIST_DIR}/src/blockchain/storage/*.cpp"
                # "${CMAKE_CURRENT_LIST_DIR}/src/blockchain/net/*.cpp"
                
add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} cryptopp) # pthread
