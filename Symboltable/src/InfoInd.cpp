#include <string.h>
#include "../includes/InfoInd.h"

InfoInd::InfoInd(char *value, int x, int y) {
	this->name = value;
	this->x = x;
	this->y = y;
}

bool InfoInd::compareLex(char * lexem)
{
	return strcmp(this->name,lexem) == 0;
	/*char* tmp = name;
	while (*tmp != '\0') {
		if (*tmp != *lexem) {
			return false;
		}
		tmp++;
		lexem++;
	}
	return *tmp == *lexem;
	 */
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
