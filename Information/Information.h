//
// Created by fble on 12/1/15.
//

#ifndef COMPILER_INFORMATION_H
#define COMPILER_INFORMATION_H

class Information {
public:
    virtual char *getInfo() = 0;

    virtual int getX() = 0;

    virtual int getY() = 0;
};

#endif //COMPILER_INFORMATION_H
