//
// Created by Dmitry on 27.09.2020.
//

#include "Acid.h"

const std::string &Acid::getName() const {
    return name;
}

void Acid::setName(const std::string &name) {
    Acid::name = name;
}

bool Acid::operator==(const Acid &b) const {

    return !(*this != b);
}

bool Acid::operator!=(const Acid &b) const {
    return toString() != b.toString();
}


