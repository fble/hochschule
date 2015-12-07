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

class InfoToken : public Information {
    char *value;
public:
    InfoToken(char *value) {
        this->value = new char(strlen(value));
        strcpy(this->value, value);
    };

    virtual ~InfoToken() { };

    virtual char *getInfo() override { return value; };

    virtual int getX() override { return -1; };

    virtual int getY() override { return -1; };
};

#endif
