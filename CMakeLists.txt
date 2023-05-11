cmake_minimum_required(VERSION 3.0.0)
project(linux-shorts VERSION 0.1.0)

include(CTest)
enable_testing()


add_executable(linux-shorts main.cpp)
add_executable(linux-shorts-fs-write src/filesystem/wirte.cpp)
add_executable(linux-shorts-fs-read src/filesystem/read.cpp)
add_executable(linux-shorts-fs-copy-host src/filesystem/copy_hosts.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
