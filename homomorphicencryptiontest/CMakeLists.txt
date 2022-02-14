cmake_minimum_required(VERSION 3.16)
project(encryptionTest)

set(CMAKE_CXX_STANDARD 17)

set(INC_DIR /usr/local/include)
set(LINK_DIR /usr/local/lib)

INCLUDE_DIRECTORIES(paillier)
include_directories(include)
INCLUDE_DIRECTORIES(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(encryptionTest main.cpp paillier/paillier.h paillier/paillier.cpp)
add_executable(elgamal elgamal.cpp)
add_executable(helibtest helibtest.cpp)
add_executable(tfhe tfhe.cpp)

target_link_libraries(encryptionTest ntl)
target_link_libraries(elgamal ntl)
target_link_libraries(helibtest helib)
target_link_libraries(tfhe tfhe-spqlios-fma)
find_package(helib REQUIRED)
