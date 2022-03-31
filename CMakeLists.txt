cmake_minimum_required(VERSION 3.12)
project(ippr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS -fpermissive -O3)

include_directories(include)

link_directories(lib)

add_executable(ippr jpeg.cpp jpegwrite.cpp ddraw.cpp util.cpp morpho.cpp border.cpp pca.cpp feature.cpp main.cpp)

if(APPLE)
    target_link_libraries(ippr libjpeg_mac.a libturbojpeg_mac.a)
else()
    target_link_libraries(ippr libjpeg_linux.a libturbojpeg_linux.a)
endif()