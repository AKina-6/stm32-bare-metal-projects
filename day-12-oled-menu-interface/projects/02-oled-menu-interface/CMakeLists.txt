cmake_minimum_required(VERSION 3.16)
project(oled_menu_interface C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(menu_core
    src/app/menu.c
    src/app/menu_renderer.c
)

target_include_directories(menu_core PUBLIC include)

add_library(host_display
    src/platform/host/host_display.c
)

target_include_directories(
    host_display PUBLIC src/platform/host
)

add_executable(oled_menu_sim
    src/platform/host/host_main.c
)

target_link_libraries(
    oled_menu_sim PRIVATE menu_core host_display
)

enable_testing()

add_executable(test_menu tests/test_menu.c)
target_link_libraries(test_menu PRIVATE menu_core)
add_test(NAME menu_state_tests COMMAND test_menu)

add_executable(test_renderer tests/test_renderer.c)
target_link_libraries(
    test_renderer PRIVATE menu_core host_display
)
add_test(NAME menu_renderer_tests COMMAND test_renderer)
