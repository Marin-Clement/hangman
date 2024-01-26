cmake_minimum_required(VERSION 3.27)
project(hangman C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(hangman
        dictionary.c
        hangman.c
        hangman.h)
