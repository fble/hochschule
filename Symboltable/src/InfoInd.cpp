#include "../includes/InfoInd.h"

InfoInd::InfoInd(char * lexem, int x, int y)
{
	this->name = lexem;
	this->x = x;
	this->y = y;
}

bool InfoInd::compareLex(char * lexem)
{
	char* tmp = name;
	while (*tmp != '\0') {
		if (*tmp != *lexem) {
			return false;
		}
		tmp++;
		lexem++;
	}
	return *tmp != *lexem ? false : true;
}

char * InfoInd::getInfo()
{
	return name;
}

int InfoInd::getX()
{
	return x;
}

int InfoInd::getY()
{
	return y;
}


