#include "BCSAlphaString.hpp"

BCSAlphaString::BCSAlphaString(int n) {
    this->size = n;
    this->setBCSAlphaString(" ");
}

BCSAlphaString::BCSAlphaString(int n, const std::string str) {
    this->size = n;
    this->setBCSAlphaString(str);
}

void BCSAlphaString::operator = (const std::string str) {
    this->setBCSAlphaString( str );
}

void BCSAlphaString::setBCSAlphaString(const std::string str) {
    if (str.size() > this->size) {
        this->value = str.substr(0,this->size);
    } else if (str.size() < this->size ) {
        this->value = str + std::string( this->size - str.size(), ' ');
    } else { // str.size == this->size
        this->value = str;
    }
}

void BCSAlphaString::toBuffer(char * buffer) {
    // WARNING: The assumption here is that the buffer has enough
    //   room for all the characters in the string
    for(int i = 0; i < this->size; i++) {
        buffer[i] = this->value[i];
    }
}

void BCSAlphaString::fromBuffer(char * buffer) {
    for (int i = 0; i < this->size; i++) {
        this->value[i] = buffer[i];
    }
}

std::string BCSAlphaString::toString() {
    return this->value;
}

int BCSAlphaString::getSize() {
    return this->size;
}
