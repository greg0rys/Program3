cmake_minimum_required(VERSION 3.23)
project(Program3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Program3 Message.h Message.cpp Contact.cpp Contact.h driver.cpp
        msgTree.cpp msgTree.h Phone.cpp Phone.h)
