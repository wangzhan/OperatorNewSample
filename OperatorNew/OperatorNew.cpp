// OperatorNew.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <new>


class COp1
{
public:
    COp1(int i) : m_i(i) { std::cout << "COp1 construct " << m_i << std::endl; }
    ~COp1() { std::cout << "COp1 destruct " << m_i << std::endl; }

    int m_i;
};

class COp2
{
public:
    COp2(int i) : m_i(i) { std::cout << "COp2 construct " << m_i << std::endl; }
    ~COp2() { std::cout << "COp2 destruct " << m_i << std::endl; }

    void* operator new (size_t size, char *lpszData) throw (std::bad_alloc)
    {
        std::cout << "COp2 new " << lpszData << std::endl;
        return malloc(size);
    }

    int m_i;
};

void test()
{
    int *p1 = new int;

    // operator new
    void *p2 = operator new (sizeof(COp1));
    
    // placement new
    COp1 *p2_2 = (COp1*) new (p2) COp1(1);

    p2_2->~COp1();

    operator delete (p2_2);

    std::cout << std::endl;

    // new operator
    COp1 *p3 = new COp1(2);
    delete p3;

    std::cout << std::endl;

    COp2 *p4 = new ("hello") COp2(1);
    delete p4;

    // TODO: illegal usege
    //void *p5 = operator new (sizeof(COp2), "hello");
    //COp2 *p5_2 = (COp2*) ::new (p5) COp2(2);
    //p5_2->~COp2();
    //operator delete(p5_2);
}

int _tmain(int argc, _TCHAR* argv[])
{
    test();

    std::cout << std::endl << "Press any key to continue..." << std::endl;
    getchar();
	return 0;
}

