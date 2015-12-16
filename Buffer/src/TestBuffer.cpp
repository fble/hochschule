#include "../includes/Buffer.h"
#include <iostream>
using namespace std;


int main(int argc, char **argv) {

	Buffer*  buffer;

	buffer = new Buffer("/home/fble/Desktop/hochschule/readme.txt");

	while(true) {
		char a = *buffer->getChar();
		if(a != '\0') cout << a;
		else break;
	}

}