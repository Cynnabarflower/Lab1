//
// Created by Dmitry on 27.09.2020.
//

#ifndef UNTITLED51_ACID_H
#define UNTITLED51_ACID_H


#include <string>

class Acid {
public:
    const std::string &getName() const;

    void setName(const std::string &name);

    bool operator==(const Acid &b);

    bool operator!=(const Acid &b);

    virtual std::string toString() const = 0;

    bool operator==(const Acid& other_) const;
    bool operator!=(const Acid& other_) const;

public:


protected:
    std::string name = "";
};


#endif //UNTITLED51_ACID_H
