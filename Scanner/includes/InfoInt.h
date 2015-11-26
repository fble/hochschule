/*
 * InformationToken.h
 *
 *  Created on: 13.11.2015
 *      Author: ubuntu-gnome
 */

#ifndef SCANNER_INCLUDES_INFOINT_H_
#define SCANNER_INCLUDES_INFOINT_H_

#include "../../Symboltable/includes/Information.h"

class InfoInt : public Information<long> {
	long value;
public:
	InfoInt(long value);

    virtual ~InfoInt();

    long getInfo() override;

    int getX() override { return -1; };

    int getY() override { return -1; };
};

#endif
