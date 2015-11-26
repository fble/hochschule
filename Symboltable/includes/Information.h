/*
* Information.h
*
*  Created on: 27.10.2015
*      Author: fble
*/

#ifndef SYMBOLTABLE_INCLUDES_INFORMATION_H_
#define SYMBOLTABLE_INCLUDES_INFORMATION_H_
template <typename T>
class Information {
public:
	virtual T getInfo() = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
};

#endif /* SYMBOLTABLE_INCLUDES_INFORMATION_H_ */
