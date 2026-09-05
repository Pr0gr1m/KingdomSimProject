cmake_minimum_required(VERSION 4.2)
project(KingdomSimProject)

set(CMAKE_CXX_STANDARD 26)

add_executable(KingdomSimProject src/main.cpp
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
        src/Race.h)
