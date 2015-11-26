//
// Created by fble on 11/26/15.
//

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H
template<typename T>
    class Token{
    public:

        virtual int getLine() = 0;

        virtual int getColumn() = 0;

        virtual Information<T>* getInformation() = 0;

        virtual TType getType() = 0;
    };
#endif //COMPILER_TOKEN_H
