#include "myiterator.h"

MyIterator::MyIterator(Node *p) : p(p){}

MyIterator::MyIterator(const MyIterator& it) : p(it.p){}

bool MyIterator::operator!=(MyIterator const& other) const
{
    return p != other.p;
}

bool MyIterator::operator==(MyIterator const& other) const
{
    return p == other.p;
}

typename MyIterator::reference MyIterator::operator*()
{
    return p;
}


MyIterator &MyIterator::operator++()
{
    p = p->next;
    return *this;
}
