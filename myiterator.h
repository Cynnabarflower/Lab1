#ifndef MYITERATOR_H
#define MYITERATOR_H

#include "node.h"





class MyIterator: public std::iterator<std::input_iterator_tag, Node*>
{
    friend class Protein;
private:
    MyIterator(Node* p);
public:
    MyIterator(const MyIterator &it);
    bool operator!=(MyIterator const& other) const;
    bool operator==(MyIterator const& other) const;
    typename MyIterator::reference operator*();
    MyIterator& operator++();
    Node *p;
};

#endif // MYITERATOR_H
