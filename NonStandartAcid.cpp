//
// Created by Dmitry on 27.09.2020.
//

#include "NonStandartAcid.h"

NonStandartAcid::NonStandartAcid(const std::string &name) {
    setName(name);
}

std::string NonStandartAcid::toString() const{
    return "N" + getName();
}

