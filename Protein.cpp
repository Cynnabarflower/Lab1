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

Protein::Protein() {
    this->m_size = 0;
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

void Protein::pushBack(Acid* element_) {
    if (m_last == nullptr) {
        assert(m_size == 0);
        assert(m_first == nullptr);
        m_first = new ElementWrapper(element_);
        m_last = m_first;
    } else {
        assert(m_last->next == nullptr);
        m_last = (m_last->next = new ElementWrapper(element_, m_last, nullptr));
    }
    ++m_size;
}

void Protein::pushFront(Acid* element_) {
    if (m_last == nullptr) {
        assert(m_size == 0);
        assert(m_first == nullptr);
        m_first = new ElementWrapper(element_);
        m_last = m_first;
    } else {
        assert(m_first->prev == nullptr);
        m_first = (m_first->prev = new ElementWrapper(element_, nullptr, m_first));
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
    while (counter < pos && p->next != nullptr) {
        p = p->next;
        counter++;
    }

    if (p->prev != nullptr) {
       temp->prev = p->prev;
       p->prev->next = temp;
    }

    temp->next = p;
    p->prev = temp;

    if (m_first == p) {
        m_first = temp;
    }

    m_size++;
}


void Protein::remove(Acid *a) {

    auto p = m_first;
    while (p->element != a && p->next != nullptr) {
        p = p->next;
    }
    assert(p == nullptr);

    if (p->prev)
        p->prev->next = p->next;
    if (p->next)
        p->next->prev = p->prev;
    if (m_first == p)
        m_first = p->next;
    if (m_last == p)
        m_last = p->prev;
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
    while (counter < pos && p->next != nullptr) {
        p = p->next;
        counter++;
    }

    if (p->prev)
        p->prev->next = p->next;
    if (p->next)
        p->next->prev = p->prev;
    if (m_first == p)
        m_first = p->next;
    if (m_last == p)
        m_last = p->prev;
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
        assert(m_first->prev == nullptr);
        assert(m_first->next == nullptr);
        assert(m_size == 1);
        delete m_first;
        m_first = (m_last = nullptr);
    } else {
        auto tmp = m_last;
        m_last = m_last->prev;
        m_last->next = nullptr;
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
        assert(m_first->prev == nullptr);
        assert(m_first->next == nullptr);
        assert(m_size == 1);
        delete m_first;
        m_first = (m_last = nullptr);
    } else {
        auto tmp = m_first;
        m_first = m_first->next;
        m_first->prev = nullptr;
        delete tmp;
    }
    --m_size;
}

size_t Protein::size() const { return m_size; }

Acid*& Protein::operator[](size_t n_) {
    if (n_ >= m_size) {
        throw std::out_of_range("n_ >= m_size");
    }
    auto tmp = m_first;
    assert(tmp != nullptr);
    for (size_t i = 0; i < n_; ++i) {
        assert(tmp != nullptr);
        tmp = tmp->next;
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
        tmp = tmp->next;
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

Acid* const & Protein::operator[](size_t n_) const {
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

Protein::ElementWrapper::ElementWrapper(Acid*& element_, Protein::ElementWrapper *left_, Protein::ElementWrapper *right_) :
    element{element_}, prev{left_}, next{right_} {
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

Acid* Protein::Iterator::operator*() {
    return element->element;
}

Protein::Iterator Protein::Iterator::operator++(int) {
    auto retVal = *this;
    element = element->next;
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
           if (p->element->operator==(*b.m_first->element)) {
               auto q = p;
               auto t = b.m_first;
               while (q != nullptr) {
                   if (*q->element != *t->element) {
                       break;
                   }
                   t = t->next;
                   q = q -> next;
               }
               if (q == nullptr) {
                       Protein result = Protein(a);
                       while(t) {
                           result.pushBack(t->element);
                           t = t -> next;
                       }
                       return result;
               }
           }
           p = p->next;

       }
       auto from = b.m_first;
       Protein result = Protein(a);
       while(from) {
           result.pushBack(from->element);
           from = from -> next;
       }
       return result;

}


