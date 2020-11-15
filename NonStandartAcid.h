//
// Created by Dmitry on 27.09.2020.
//

#ifndef UNTITLED51_NONSTANDARTACID_H
#define UNTITLED51_NONSTANDARTACID_H


#include "Amino.h"

class NonStandartAcid : public Acid {
public:
    NonStandartAcid(const std::string &name);

    virtual std::string toString() const;
};


#endif //UNTITLED51_NONSTANDARTACID_H
