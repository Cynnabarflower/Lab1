#include "Amino.h"
#include "NonStandartAcid.h"
#include "Protein.h"

#include <QString>
#include <QTextStream>
#include <qfile.h>

size_t constexpr MAX_SIZE = 100000;

void printLinkedList(const Protein &list_) {
    bool first = true;
    int counter = 0;
    for (const auto& element : list_) {
        if (!first) {
            std::cout << "; ";
        }
        std::cout << counter++ << " ";
        first = false;
        std::cout << element->toString();
    }
    std::cout << std::endl;
}

Protein::Protein(size_t n_) {
    for (size_t i = 0; i < n_; ++i) {
        pushBack(nullptr);
    }
}

Protein::Protein(const Protein &other_) {
    for (size_t i = 0; i < other_.size(); ++i) {
        this->pushBack(other_[i]);
    }
}

Protein &Protein::operator=(Protein &&other_) {
    if (this == &other_) {
        return *this;
    }
    this->clear();
    this->m_first = other_.m_first;
    this->m_last = other_.m_last;
    this->m_size = other_.m_size;
    other_.m_first = other_.m_last = nullptr;
    other_.m_size = 0;
    return *this;
}

void Protein::pushBack(const Acid *element_) {
    if (m_last == nullptr) {
        assert(m_size == 0);
        assert(m_first == nullptr);
        m_first = new ElementWrapper(element_);
        m_last = m_first;
    } else {
        assert(m_last->right == nullptr);
        m_last = (m_last->right = new ElementWrapper(element_, m_last, nullptr));
    }
    ++m_size;
}

void Protein::pushFront(const Acid *element_) {
    if (m_last == nullptr) {
        assert(m_size == 0);
        assert(m_first == nullptr);
        m_first = new ElementWrapper(element_);
        m_last = m_first;
    } else {
        assert(m_first->left == nullptr);
        m_first = (m_first->left = new ElementWrapper(element_, nullptr, m_first));
    }
    ++m_size;
}


void Protein::insert( Acid* element_, int pos) {
    assert((pos > 0 && pos <= size()) || pos == 0);

    if (pos == size()) {
        pushBack(element_);
        return;
    }

    ElementWrapper *temp = new ElementWrapper(element_, nullptr, nullptr);
    int counter = 0;
    auto p = m_first;
    while (counter < pos && p->right != nullptr) {
        p = p->right;
        counter++;
    }

    if (p->left != nullptr) {
       temp->left = p->left;
       p->left->right = temp;
    }

    temp->right = p;
    p->left = temp;

    if (m_first == p) {
        m_first = temp;
    }

    m_size++;
}


void Protein::remove(Acid *a) {

    auto p = m_first;
    while (p->element != a && p->right != nullptr) {
        p = p->right;
    }
    assert(p == nullptr);

    if (p->left)
        p->left->right = p->right;
    if (p->right)
        p->right->left = p->left;
    if (m_first == p)
        m_first = p->right;
    if (m_last == p)
        m_last = p->left;
    delete p;

    --m_size;

}


void Protein::remove(int pos) {

    assert(pos >= 0 && pos < size());

    if (pos == 0) {
        popFront();
        return;
    }
    if (pos == size() - 1) {
        popBack();
        return;
    }
    int counter = 0;
    auto p = m_first;
    while (counter < pos && p->right != nullptr) {
        p = p->right;
        counter++;
    }

    if (p->left)
        p->left->right = p->right;
    if (p->right)
        p->right->left = p->left;
    if (m_first == p)
        m_first = p->right;
    if (m_last == p)
        m_last = p->left;
    delete p;

    --m_size;

}


void Protein::popBack() {
    if (m_last == nullptr) {
        assert(m_size == 0);
        assert(m_first == nullptr);
        return;
    }
    if (m_first == m_last) {
        assert(m_first->left == nullptr);
        assert(m_first->right == nullptr);
        assert(m_size == 1);
        delete m_first;
        m_first = (m_last = nullptr);
    } else {
        auto tmp = m_last;
        m_last = m_last->left;
        m_last->right = nullptr;
        delete tmp;
    }
    --m_size;
}

void Protein::popFront() {
    if (m_last == nullptr) {
        assert(m_size == 0);
        assert(m_first == nullptr);
        return;
    }
    if (m_first == m_last) {
        assert(m_first->left == nullptr);
        assert(m_first->right == nullptr);
        assert(m_size == 1);
        delete m_first;
        m_first = (m_last = nullptr);
    } else {
        auto tmp = m_first;
        m_first = m_first->right;
        m_first->left = nullptr;
        delete tmp;
    }
    --m_size;
}

size_t Protein::size() const { return m_size; }

const Acid *Protein::operator[](size_t n_) {
    //return const_cast<Element&>(const_cast<const LinkedList&>(*this)[n_]);
    if (n_ >= m_size) {
        throw std::out_of_range("n_ >= m_size");
    }
    auto tmp = m_first;
    assert(tmp != nullptr);
    for (size_t i = 0; i < n_; ++i) {
        assert(tmp != nullptr);
        tmp = tmp->right;
    }
    return tmp->element;
}

void Protein::clear() {
    if (m_size == 0) {
        assert(m_first == nullptr);
        assert(m_last == nullptr);
        return;
    }
    auto tmp = m_first;
    assert(tmp != nullptr);
    for (size_t i = 0; i < m_size; ++i) {
        assert(tmp != nullptr);
        auto tmp2 = tmp;
        tmp = tmp->right;
        delete tmp2;
    }
    m_first = m_last = nullptr;
    m_size = 0;
}

bool Protein::operator==(const Protein &other_) const {
    if (m_size != other_.m_size) {
        return false;
    }
    auto it2 = other_.begin();
    for (const auto& e1 : (*this)) {
        int a = 234;
        if (*e1 != *(*it2)) {
            return false;
        }
        ++it2;
    }
    return true;
}

bool Protein::operator!=(const Protein &other_) const {
    return !((*this) == other_);
}

Protein::Iterator Protein::begin() {
    return m_first;
}

Protein::Iterator Protein::end() {
    return nullptr;
}

Protein::Iterator Protein::begin() const {
    return m_first;
}

Protein::Iterator Protein::end() const {
    return nullptr;
}

const Acid *Protein::operator[](size_t n_) const {
    return const_cast<Protein&>(*this)[n_];
}

Protein &Protein::operator=(const Protein &other_) {
    if (this == &other_) {
        return *this;
    }
    this->clear();
    for (size_t i = 0; i < other_.size(); ++i) {
        this->pushBack(other_[i]);
    }
    return *this;
}

Protein::ElementWrapper::ElementWrapper(const Acid *element_, Protein::ElementWrapper *left_, Protein::ElementWrapper *right_) :
    element{element_}, left{left_}, right{right_} {
    this->element = element_;
}

Protein::Iterator::Iterator(Protein::ElementWrapper *element_) : element{element_} { }

bool Protein::Iterator::operator!=(const Protein::Iterator &other_) {
    return element != other_.element;
}

Protein::Iterator& Protein::Iterator::operator++() {
    (*this)++;
    return *this;
}

const Acid *Protein::Iterator::operator*() {
    return element->element;
}

Protein::Iterator Protein::Iterator::operator++(int) {
    auto retVal = *this;
    element = element->right;
    return retVal;
}


int Protein::saveToFile(const std::string &filename) const {

    QFile data(QString::fromStdString(filename));
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        for (auto a : *this)
        {
           out << QString::fromStdString(a->toString()) << "\n";

        }
    }
    data.close();
    return 0;
}


int Protein::loadFromFile(const std::string &filename) {

    QFile data(QString::fromStdString(filename));
    if (data.open(QFile::ReadOnly)) {
        this->clear();
        QTextStream in(&data);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("A")) {
                auto lstLine = line.remove(0, 1).split(", ");
               pushBack(new Amino(lstLine.first().trimmed().toUtf8().data(), *lstLine.last().trimmed().toUtf8().data()));
            } else if (line.startsWith("N")) {
                pushBack(new NonStandartAcid(line.remove(0, 1).trimmed().toUtf8().begin()));
            }
        }

    }
    return 0;

}


Protein operator+(const Protein &a, const Protein &b) {
    if (!a.m_last) {
           return Protein(b);
       } else if (!b.m_first) {
           return Protein(a);
       }

       auto p = a.m_first;
       while (p != nullptr) {
           if (*p->element == *b.m_first->element) {
               auto q = p;
               auto t = b.m_first;
               while (q != nullptr) {
                   if (*q->element != *t->element) {
                       break;
                   }
                   t = t->right;
                   q = q -> right;
               }
               if (q == nullptr) {
                       Protein result = Protein(a);
                       while(t) {
                           result.pushBack(t->element);
                           t = t -> right;
                       }
                       return result;
               }
           }
           p = p->right;

       }
       auto from = b.m_first;
       Protein result = Protein(a);
       while(from) {
           result.pushBack(from->element);
           from = from -> right;
       }
       return result;

}


