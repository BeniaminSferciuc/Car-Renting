cmake_minimum_required(VERSION 3.25)
project(Project___POO)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project___POO main.cpp include/Vehicle.h include/Client.h include/Rental.h include/Administrator.h src/Vehicle.cpp src/Client.cpp src/Rental.cpp src/Administrator.cpp utils/utils.h utils/utils.cpp utils/MenuAdmin.cpp utils/MenuAdmin.h utils/MainFunctions.h utils/MainFunctions.cpp)
