cmake_minimum_required(VERSION 3.26)
project(WEBServer C)

set(CMAKE_C_STANDARD 99)

add_executable(WEBServer main.c auxfunc.c client_API.c header.h)
add_executable(client client.c header.h)
add_executable(auxfunc auxfunc.c auxfunc.h header.h)
add_executable(client_API client_API.c client_API.h header.h)


target_link_libraries(client w2_s32)
