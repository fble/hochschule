//#include "../includes/AutomatSign.h"
//#include "../includes/AutomatInteger.h"
//#include "../includes/AutomatIdentifier.h"
#include "../includes/AutomatManager.h"
#include <iostream>
using namespace std;

const int length = 5;
int factor = 1;
char test[length];
int ctr = 0;

void output(int ctr, AutomatManager* manager) {
	cout << ctr << " Zeichen gehören zu der Sprache" << endl;
	cout << "Zeichen Nummer " << ctr+1 << " führt zum Verwerfen des Automaten!" << endl;

	char* type;

	switch(manager->getType()) {
		case Integer: type = "Integer"; break;
		case Identifier: type = "Identifier"; break;
		case Sign: type = "Sign"; break;
		case Fehler: type = "Fehler"; break;
		case Error: type = "Nicht eindeutig"; break;
		case If: type = "If"; break;
		case While: type = "While"; break;
		default: type = "NoType";
	}
	cout << "Der Token ist vom Typ " << type << endl;
}

int main (int argc, char* argv[]) {
	char* testString = "=";

	AutomatManager* manager = new AutomatManager();

	int ctr = 0;

	while(*testString != '\0') {
		bool tmp = manager->readChar(*testString);

		if(tmp) ctr++;

		testString++;
	}

	output(ctr, manager);

}



void Test1() {
	/*int signElements = 16;

	char* lexemeSign[] = {
			"<:>", "+", ":=", "=:", "?", "&&", "[", ";", "!", "<:><", "<?", "?<",
			"<", ">", ":", "-", "*"
	};

	Automat* automat = new AutomatSign();

	for(int i = 0; i<signElements; i++) {
		int ctr = 0;
		while(*(lexemeSign[i]) != '\0') {
			automat->readChar(*(lexemeSign[i]));

			lexemeSign[i]++;
			ctr++;
		}

		if(!automat->isFinal()) {
			cout << "Nach " << automat->charCtr << " Zeichen verworfen" << "   ";
		}
		cout << lexemeSign[i]-ctr << " wird zu " << automat->isFinal() << endl;
		automat->reset();
	}

	cout << endl;

	const int intElements = 5;

	char* lexemeInt[intElements] = {"0", "01", "1234", "14i", "w1234"};

	AutomatInteger* automatInt = new AutomatInteger();

	for(int i = 0; i<intElements; i++) {
		int ctr = 0;
		while(*(lexemeInt[i]) != '\0') {
			automatInt->readChar(*(lexemeInt[i]));
			lexemeInt[i]++;
			ctr++;
		}

		if(!automatInt->isFinal()) {
			cout << "Nach " << automatInt->charCtr << " Zeichen verworfen" << "   ";
		}
		cout << lexemeInt[i]-ctr << " wird zu " << automatInt->isFinal() << endl;
		automatInt->reset();
	}

	cout << endl;

	const int idenElements = 5;

	char* lexemeIden[idenElements] = {"abc", "a1d3r5", "a b", "1a d", "1abc"};

	AutomatIdentifier* automatIden = new AutomatIdentifier();

	for(int i = 0; i<idenElements; i++) {
		int ctr = 0;
		while(*(lexemeIden[i]) != '\0') {
			automatIden->readChar(*(lexemeIden[i]));
			lexemeIden[i]++;
			ctr++;
		}

		if(!automatIden->isFinal()) {
			cout << "Nach " << automatIden->charCtr << " Zeichen verworfen" << "   ";
		}

		cout << lexemeIden[i]-ctr << " wird zu " << automatIden->isFinal() << endl;
		automatIden->reset();
	}*/
}