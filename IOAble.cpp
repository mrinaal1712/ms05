#include "IOAble.h"
#include <iostream>
using namespace std;
namespace sdds
{
    ostream& operator<<(ostream& ostr, const IOAble& obj)
    {
        obj.write(ostr);
        return ostr;
    }
    istream& operator>>(istream& istr, IOAble& obj)
    {
        obj.read(istr);
        return istr;
    }
}
