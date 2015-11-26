/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Buffer.h"

Buffer::Buffer() {
	index = 0;
	
	createBufSize();

	cout << "BUFFER_SIZE: " << BUFFER_SIZE << endl;

	// Datei mit Pfad und Modus öffnen
	file_descripter = open("/home/ubuntu-gnome/file.txt", O_RDONLY | O_DIRECT);

	if(file_descripter < 0) {
		cout << "Error";
	}

	// n bytes Speicher reservierung mit 1024 bytes Ausrichtung
	// In buf wird der Zeiger, der zu diesem Speicherbereich führt, abgelegt
	posix_memalign(&buf1, ALIGNMENT, BUFFER_SIZE*sizeof(char));

	bytes_read = read(file_descripter, buf1, BUFFER_SIZE);

	currentChar = *((char*) buf1); 	// !! NUR FÜR TEST

	cout << "READ: " << bytes_read << endl;
}

void Buffer::createBufSize() {
	if(stat("/home/fble/Desktop/Compiler/Symboltable", &statbuf) == -1) {
		cout << "Fehler";
	}

	int tmp = 1;
	int i = 0;
	for(i = 0; tmp < statbuf.st_size; i++) {
		int a = 1;
		for(int j = 0; j<i; j++) {
			a *= 2;
		}
		tmp = a;
	}

	BUFFER_SIZE = tmp;
}

char* Buffer::getChar() {
	int i = index;
	char* a = (char*) buf1;
	index++;

	currentChar = *(a+i); // !!! NUR FÜR TEST

	return (a+i);
}

char Buffer::getCurrentChar() { // !!!! NUR FÜR TEST
	return currentChar;
}

char* Buffer::getCharPointer() {
	char* a = (char*) buf1;

	return a+index;
}

Buffer::~Buffer() {
	// TODO Auto-generated destructor stub
}
