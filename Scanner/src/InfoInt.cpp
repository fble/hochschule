#include "../includes/InfoInt.h"

InfoInt::InfoInt(long value) {
    this->value = value;
}

long InfoInt::getInfo() {
    return value;
}

InfoInt::~InfoInt() {
}
