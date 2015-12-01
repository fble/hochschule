/*
* InfoInd.h
*
*  Created on: 27.10.2015
*      Author: fble
*/

#ifndef SYMBOLTABLE_INCLUDES_INFOIND_H_
#define SYMBOLTABLE_INCLUDES_INFOIND_H_

#include "../../Information/Information.h"

class InfoInd : public Information {
private:
	char* name;
	int x;
	int y;
public:
	InfoInd(char *value, int x, int y);
	bool compareLex(char* lexem);

	char *getInfo() override;

	int getX() override;

	int getY() override;
};

#endif /* SYMBOLTABLE_INCLUDES_INFOIND_H_ */
