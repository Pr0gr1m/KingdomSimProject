cmake_minimum_required(VERSION 4.2)

include("${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

#if(WIN32 AND NOT MSVC)
#    set(VCPKG_TARGET_TRIPLET "x64-mingw-static" CACHE STRING "Vcpkg target triplet" FORCE)
#endif()

set(ProjectName "KingdomSimProject")
project(${ProjectName})

set(CMAKE_CXX_STANDARD 26)

find_package(fmt CONFIG REQUIRED)

add_executable(${ProjectName} src/main.cpp
        src/JobType.cpp
        src/JobType.h
        src/Individual.cpp
        src/Individual.h
        src/Kingdom.cpp
        src/Kingdom.h
        src/Strike.cpp
        src/Strike.h
        src/SocialClass.cpp
        src/SocialClass.h
        src/Race.h
        EnumToString.cpp
        EnumToString.h
        EnumToString.h)

target_link_libraries(${ProjectName} PRIVATE fmt::fmt)