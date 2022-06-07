cmake_minimum_required(VERSION 3.16)
project(logistics_management_system)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(logistics_management_system
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
        src/WarehouseUser.cpp)
