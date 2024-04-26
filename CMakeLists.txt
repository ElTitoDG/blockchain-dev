cmake_minimum_required(VERSION 3.28.1)

# Declaramos la variable del nombre del projecto
set(PROJECT_NAME "blockchain-dev")

# Declaramos el nombre del projecto
set(${PROJECT_NAME})

FILE(GLOB SRCS "${CMAKE_CURRENT_LIST_DIR}/src/blockchain/*.cpp"
                "${CMAKE_CURRENT_LIST_DIR}/src/blockchain/storage/*.cpp"
                "${CMAKE_CURRENT_LIST_DIR}/src/blockchain/net/*.cpp"
                "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ssl crypto pthread)
