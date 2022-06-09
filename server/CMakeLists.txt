cmake_minimum_required(VERSION 3.16)
project(server)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(server
        src/main.cpp
        src/Console.cpp
        src/Console.h
        src/History.cpp
        src/History.h
        src/Manager.cpp
        src/ManagerMenu.cpp
        src/Menu.cpp
        src/Menu.h
        src/Package.cpp
        src/Package.h
        src/User.cpp
        src/User.h
        src/UserMenu.cpp
        src/Utils.cpp
        src/Utils.h
        src/Courier.cpp
        src/CourierMenu.cpp
        src/WarehouseCourier.cpp
        src/Warehouse.cpp
        src/Warehouse.h
        src/WarehouseManager.cpp
        src/WarehouseUser.cpp
        src/ServerSocket.h
        src/ServerSocket.cpp
        src/ClientSocket.h
        src/ClientSocket.cpp
        )
