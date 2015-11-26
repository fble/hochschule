/*
* InfoInd.h
*
*  Created on: 27.10.2015
*      Author: fble
*/

#ifndef SYMBOLTABLE_INCLUDES_INFOIND_H_
#define SYMBOLTABLE_INCLUDES_INFOIND_H_

#include "../includes/Information.h"
class InfoInd : public Information<char*> {
private:
	char* name;
	int x;
	int y;
public:
	InfoInd(char* lexem, int x, int y);
	bool compareLex(char* lexem);
	char* getInfo();
	int getX();
	int getY();
};

#endif /* SYMBOLTABLE_INCLUDES_INFOIND_H_ */
