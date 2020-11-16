#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Acid.h"

#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <fstream>

class Protein {
public:
    Protein();
    Protein(const Protein& other_);
    ~Protein() { clear(); };
    Protein& operator=(const Protein& other_);
    Protein& operator=(Protein&& other_);
    void pushBack(Acid* element_);
    void pushFront(Acid* element_);
    void popBack();
    void popFront();
    size_t size() const;
    Acid*& operator[](size_t n_) const;
    Acid*& operator[](size_t n_);
    void clear();
    bool operator==(const Protein& other_) const;
    bool operator!=(const Protein& other_) const;
    int loadFromFile(const std::string &filename);
    int saveToFile(const std::string &filename) const;
    void remove(Acid *a);
    void remove(int pos);
    void insert(Acid* element_, int i);
    friend Protein operator+(const Protein& a, const Protein& b);
private:
    class ElementWrapper {
    public:
        ElementWrapper(Acid*& element_,
                       ElementWrapper* left_ = nullptr,
                       ElementWrapper* right_ = nullptr);
        Acid* element;
        ElementWrapper* left{nullptr};
        ElementWrapper* right{nullptr};
    };
public:
    class Iterator {
    public:
        Iterator(ElementWrapper* element_);
        ElementWrapper* element{nullptr};
        bool operator!=(const Iterator& other_);
        Iterator operator++(int);
        Iterator& operator++();
        const Acid* operator*();
    };
    Iterator begin();
    Iterator end();
    Iterator begin() const;
    Iterator end() const;
private:
    ElementWrapper* m_first{nullptr};
    ElementWrapper* m_last{nullptr};
    size_t m_size{0};
};

void printLinkedList(const Protein& list_);

#endif // LINKEDLIST_H
