cmake_minimum_required(VERSION 3.16)

project(MonoPoly_BramJ_2025 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MonoPoly_BramJ_2025 main.cpp)

include(GNUInstallDirs)
install(TARGETS MonoPoly_BramJ_2025
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
