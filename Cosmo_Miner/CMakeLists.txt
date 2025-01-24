# CMakeList.txt: projekt CMake dla elementu Cosmo_Miner, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)

# Włącz przeładowywanie kodu XAML na gorąco dla kompilatorów MSVC, jeśli jest to obsługiwane.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Cosmo_Miner")

#set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (Cosmo_Miner "Cosmo_Miner.cpp" "Cosmo_Miner.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Cosmo_Miner PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.

include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)

    FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
    )
    FetchContent_MakeAvailable(gtest)
target_link_libraries(Cosmo_Miner PRIVATE raylib)

add_executable(Cosmo_Miner_tests "Cosmo_Miner_tests.cpp")
target_link_libraries(Cosmo_Miner_tests PRIVATE gtest gtest_main)
target_compile_options(Cosmo_Miner_tests PRIVATE "/MTd")

file(COPY ${CMAKE_SOURCE_DIR}/rsc DESTINATION ${CMAKE_BINARY_DIR})