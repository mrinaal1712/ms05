#ifndef IOABLE_H_INCLUDED
#define IOABLE_H_INCLUDED
#include<iostream>
using namespace std;
namespace sdds
{
    class IOAble
    {
    public:
        virtual ostream& csvWrite(ostream& os)const = 0;
        virtual istream& csvRead(istream& is) = 0;
        virtual ostream& write(ostream& os)const = 0;
        virtual istream& read(istream& istr) = 0;
        virtual ~IOAble() {};
    };
    ostream& operator<<(ostream& ostr, const IOAble& obj);
    istream& operator>>(istream& istr, IOAble& obj);
}



#endif // IOABLE_H_INCLUDED
