#include "../includes/AutomatManager.h"
#include <iostream>
using namespace std;

void output(AutomatManager* manager, char* testString, int ctr2) {
	char* type = manager->toString();

	cout << "Der Token ist vom Typ " << type << endl;
	cout << "Der Token beginnt bei " << ctr2 << endl;
	cout << "Die Endmarke ist bei " << manager->getEndOfChar()+ctr2 << endl;

	if(manager->getEndOfChar() == 0) {
		cout << "Das Lexem " << *(testString+ctr2);
	} else {
		char tmp[manager->getEndOfChar()];
		for(int i = 0; i<manager->getEndOfChar(); i++) {
			tmp[i] = *(testString+i+ctr2);
		}

		cout << "Das Lexem ";

		for(int i = 0; i<manager->getEndOfChar(); i++) {
			cout << tmp[i];
		}
	}


	cout << " ist somit gültig";
}

int main (int argc, char* argv[]) {
	char* testString = "x:=1+2";

	AutomatManager* manager = new AutomatManager();

	int currIndex = 0; // Speichert den absoluten Index im Array
	int relIndex = currIndex; // Speichert den Anfang einen neues Tokens

	while(*(testString + currIndex) != '\0') {
		bool tmp = manager->readChar(*(testString + currIndex));

		if(!tmp) {
			output(manager, testString, relIndex);
			cout << endl << "----------------------" << endl;
			manager->reset();
			relIndex = currIndex; // Anfang eines neuen Tokens wird aktualisiert
			currIndex--; // Die Stelle, an der der Automat verworfen hat,
		}

		currIndex++;
	}

	output(manager, testString, relIndex);

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