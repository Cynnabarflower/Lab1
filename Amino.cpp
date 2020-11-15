#include "Amino.h"

Amino::Amino(const std::string &name){
    setName(name);
}

Amino::Amino(const std::string &name, char shortName) : shortName(shortName) {
    setName(name);
}

Amino::Amino() {}


char Amino::getShortName() const {
    return shortName;
}

void Amino::setShortName(char shortName) {
    Amino::shortName = shortName;
}

std::string Amino::toString() const {
    return "A" + getName() + ", " + getShortName();
}
