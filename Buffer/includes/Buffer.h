/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>

using namespace std;

class Buffer {
private:
	static const int ALIGNMENT = 1024;
	int BUFFER_SIZE;
	int index;
	void* buf1;
	int file_descripter;
	int bytes_read;
	char currentChar;
	void createBufSize(char* filePath);
public:
	struct stat statbuf;
	Buffer(char* filePath);
	~Buffer() {delete[] buf1;};
	char* getChar();
	char* getCharPointer();
	void ungetChar(int digits);
};

#endif /* BUFFER_H_ */