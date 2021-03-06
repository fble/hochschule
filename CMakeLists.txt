cmake_minimum_required(VERSION 3.3)
project(hochschule)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Automat/includes/Automat.h
        Automat/includes/AutomatIdentifier.h
        Automat/includes/AutomatInteger.h
        Automat/includes/AutomatSign.h
        Automat/includes/AutomatManager.h
        Automat/src/Automat.cpp
        Automat/src/AutomatIdentifier.cpp
        Automat/src/AutomatInteger.cpp
        Automat/src/AutomatSign.cpp
        Automat/src/AutomatManager.cpp

        Buffer/includes/Buffer.h
        Buffer/src/Buffer.cpp

        Symboltable/includes/InfoInd.h
        Symboltable/includes/Symboltable.h
        Symboltable/includes/SymtabEntry.h
        Symboltable/src/InfoInd.cpp
        Symboltable/src/Symboltable.cpp
        Symboltable/src/SymtabEntry.cpp

        Scanner/includes/InfoError.h
        Scanner/includes/Scanner.h
        Scanner/includes/ScannerImp.h
        Scanner/includes/Token.h
        Scanner/includes/TType.h
        Scanner/src/ScannerImp.cpp

        Information/Information.h

        Scanner/src/TestScanner.cpp
        #Buffer/src/TestBuffer.cpp
        #Automat/src/TestAutomat.cpp
        #Symboltable/src/TestSymboltable.cpp
        Scanner/includes/InfoInt.h Scanner/includes/InfoInt.h)


add_executable(hochschule ${SOURCE_FILES})