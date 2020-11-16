

#include "Amino.h"
#include "NonStandartAcid.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    auto p = Protein();
    p.pushBack(new Amino("A",'a'));
    p.pushBack(new Amino("B",'b'));
    p.pushBack(new NonStandartAcid("C"));
    p.pushBack(new NonStandartAcid("D"));
    p.pushBack(new Amino("E",'e'));
    assert(p.size() == 5);


    auto p2 = Protein();
    p2.pushBack(new Amino("A",'a'));
    p2.pushBack(new Amino("B",'b'));
    p2.pushBack(new NonStandartAcid("C"));
    p2.pushBack(new NonStandartAcid("D"));
    p2.pushBack(new Amino("E",'e'));


    assert(p == p2);
    p2.remove(1);
    assert(p2.size() == 4);

    auto p3 = Protein(p2);

    assert(p3 == p2);

    p3.clear();

    assert(p3.size() == 0);

    p2.remove(0);


    p2.pushBack(new Amino("F", 'f'));

    printLinkedList(p);
    printLinkedList(p2);

    auto p4 = p + p2;

    printLinkedList(p4);

    p.pushBack(new Amino("F", 'f'));

    assert(p == p4);

    assert(p + Protein() == p4);
    assert(Protein() + p == p4);

    p.saveToFile("file1.txt");

    auto p5 = Protein();

    p5.loadFromFile("file1.txt");

    assert(p == p5);

    p[0]->setName("Z");


    assert(p[0] != p5[0]);

    p5[0]->setName("Z");

    assert(p[0] != p5[0]);

    for (auto a : p)
        a->setName("Name");

    for (auto a : p)
        assert(a->getName() == "Name");


    std::cout << "Well done!" << std::endl;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
