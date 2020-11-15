#ifndef UNTITLED51_AMINO_H
#define UNTITLED51_AMINO_H


#include <string>
#include "Acid.h"

class Amino : public Acid {

public:

    explicit Amino(const std::string &name);

    Amino();

    Amino(const std::string &name, char shortName);

    char getShortName() const;

    void setShortName(char shortName);

    virtual std::string toString() const;

private:
    char shortName = '.';
};


#endif //UNTITLED51_AMINO_H
