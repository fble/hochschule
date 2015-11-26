#include "../includes/InfoSign.h"
#include <string.h>

InfoSign::InfoSign(char* sign)
{
	this->sign = new char(strlen(sign) + 1);
	strcpy(this->sign, sign);
}

InfoSign::~InfoSign()
{
	delete[] sign;
}

char* InfoSign::getInfo()
{
	return sign;
}
