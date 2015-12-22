/*
 * InformationToken.h
 *
 *  Created on: 13.11.2015
 *      Author: ubuntu-gnome
 */

#ifndef SCANNER_INCLUDES_INFORMATION_H_
#define SCANNER_INCLUDES_INFORMATION_H_

#include <string.h>
#include "../../Information/Information.h"

class InfoError : public Information <char*>{
    char *value;
public:
    InfoError(char *value) {
        this-> value = new char(strlen(value));
        strcpy(this->value,value);
    };

    virtual ~InfoError() {};

    virtual char *getInfo() override { return value; };

    virtual int getX() override { return 0; };

    virtual int getY() override { return 0; };
};

#endif
