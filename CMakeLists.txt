cmake_minimum_required(VERSION 3.16)

project(veggieapp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(QT_MIN_VERSION "5.15.2")

find_package(
    Qt5
    ${QT_MIN_VERSION}
    REQUIRED CONFIG COMPONENTS

    Widgets
    Sql
)

add_subdirectory(src)
