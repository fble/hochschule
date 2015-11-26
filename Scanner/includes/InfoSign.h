#ifndef SCANNER_INCLUDES_INFOSIGN_H_
#define SCANNER_INCLUDES_INFOSIGN_H_
#include "../../Symboltable/includes/Information.h"
class InfoSign : public Information<char*>
{
	char* sign;
public:
	InfoSign(char* sign);

	virtual ~InfoSign();

	char* getInfo() override;

	int getX() override { return -1; };

	int getY() override { return -1; };
};
#endif