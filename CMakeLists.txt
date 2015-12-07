cmake_minimum_required(VERSION 3.3)
project(hochschule)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        #Automat/includes/Automat.h
        #Automat/includes/AutomatIdentifier.h
        #Automat/includes/AutomatInteger.h
        #Automat/includes/AutomatSign.h
        #Automat/src/Automat.cpp
        #Automat/src/AutomatIdentifier.cpp
        #Automat/src/AutomatInteger.cpp
        #Automat/src/AutomatSign.cpp
        #Automat/src/TestAutomat.cpp
        #Automat/src/AutomatManager.cpp
        #Automat/includes/AutomatManager.h
        Buffer/includes/Buffer.h
        Buffer/src/Buffer.cpp
        Buffer/src/TestBuffer.cpp
        #Symboltable/includes/InfoInd.h
        #Symboltable/includes/Symboltable.h
        #Symboltable/includes/SymtabEntry.h
        #Symboltable/src/InfoInd.cpp
        #Symboltable/src/Symboltable.cpp
        #Symboltable/src/SymtabEntry.cpp
        #Symboltable/src/TestSymboltable.cpp
        #Scanner/includes/InfoToken.h
        #Scanner/includes/Scanner.h
        #Scanner/includes/Token.h
        #Scanner/includes/TType.h
        #Scanner/src/TestScanner.cpp
        #Scanner/src/Scanner.cpp
        #Information/Information.h
        )


add_executable(hochschule ${SOURCE_FILES})