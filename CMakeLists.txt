cmake_minimum_required(VERSION 3.16)
project(SmartValetParking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(valet
    main.cpp
    CustomerData.cpp
)

target_compile_options(valet PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
)

enable_testing()

add_executable(data_structure_smoke_test
    tests/data_structure_smoke.cpp
    CustomerData.cpp
)

target_compile_options(data_structure_smoke_test PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
)

add_test(NAME data_structure_smoke
         COMMAND data_structure_smoke_test)
