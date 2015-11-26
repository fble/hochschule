cmake_minimum_required(VERSION 3.3)
project(Compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Automat/includes/Automat.h
        Automat/includes/AutomatIdentifier.h
        Automat/includes/AutomatInteger.h
        Automat/includes/AutomatSign.h
        Automat/src/Automat.cpp
        Automat/src/AutomatIdentifier.cpp
        Automat/src/AutomatInteger.cpp
        Automat/src/AutomatSign.cpp
    #Automat/src/TestAutomat.cpp
        Buffer/includes/Buffer.h
        Buffer/src/Buffer.cpp
    #Buffer/src/TestBuffer.cpp
        Scanner/includes/InfoInt.h
        Scanner/includes/InfoSign.h
        Scanner/includes/Scanner.h
        Scanner/includes/TokenInt.h
        Scanner/includes/TType.h
        Scanner/src/InfoInt.cpp
        Scanner/src/InfoSign.cpp
        Scanner/src/Scanner.cpp
        Scanner/src/TestScanner.cpp
        Scanner/src/TokenInt.cpp
        Symboltable/includes/InfoInd.h
        Symboltable/includes/Information.h
        Symboltable/includes/Symboltable.h
        Symboltable/includes/SymtabEntry.h
        Symboltable/src/InfoInd.cpp
        Symboltable/src/Symboltable.cpp
        Symboltable/src/SymtabEntry.cpp Scanner/includes/Token.h Scanner/includes/TokenChar.h Scanner/src/TokenChar.cpp Scanner/src/TokenChar.h)
    #Symboltable/src/TestSymboltable.cpp)

add_executable(Compiler ${SOURCE_FILES})