//
// Created by fble on 12/9/15.
//

#ifndef HOCHSCHULE_INFOINT_H
#define HOCHSCHULE_INFOINT_H

#include <string.h>
#include <stdlib.h>
#include "../../Information/Information.h"

class InfoInt : public Information <long>{
    long value;
public:
    InfoInt(long value) {
        this->value = value;
    };

    virtual ~InfoInt() {};

    virtual long getInfo() override { return value; };

    virtual int getX() override { return 0; };

    virtual int getY() override { return 0; };
};
#endif //HOCHSCHULE_INFOINT_H
