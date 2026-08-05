cmake_minimum_required(VERSION 3.16)
project(bh1750_light_meter C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(light_meter_core
    src/bh1750/bh1750_core.c
    src/app/light_meter.c
)

target_include_directories(light_meter_core PUBLIC include)

add_executable(bh1750_light_meter_sim
    src/platform/host/host_main.c
)

target_link_libraries(bh1750_light_meter_sim PRIVATE light_meter_core)

if(NOT MSVC)
    target_link_libraries(light_meter_core PUBLIC m)
endif()

enable_testing()

add_executable(test_bh1750_core tests/test_bh1750_core.c)
target_link_libraries(test_bh1750_core PRIVATE light_meter_core)
add_test(NAME bh1750_core_tests COMMAND test_bh1750_core)

add_executable(test_light_meter tests/test_light_meter.c)
target_link_libraries(test_light_meter PRIVATE light_meter_core)
add_test(NAME light_meter_tests COMMAND test_light_meter)
