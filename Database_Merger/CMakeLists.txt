cmake_minimum_required(VERSION 3.0)
project(Database_Merger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Database_Merger Database_Merger.cc)