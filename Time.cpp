#include "Time.h"
#include "utils.h"
#include<iomanip>
using namespace std;
namespace sdds {
    Time::Time(unsigned int min) {
        m_min = min;
    }

    Time& Time::setToNow() {
        m_min = getTime();
        return *this; //Add this
    }

    ostream& Time::write(ostream& ostr) const
    {
        int h = m_min / 60;
        int m = m_min - h * 60;

        return ostr << setfill('0') << setw(2) << h << ":" << setfill('0') << setw(2) << m;
    }

    istream& Time::read(istream& istr)
    {
        int h, m;
        char ch;
        istr >> h;
        if (h < 0)
            istr.setstate(ios::failbit);
        istr >> ch;
        if (ch != ':')
            istr.setstate(ios::failbit);
        istr >> m;
        if (m < 0)
            istr.setstate(ios::failbit);
        m_min = h * 60 + m;
        return istr;
    }

    Time& Time::operator=(unsigned int val)
    {
        return *this = Time(val);
    }

    Time Time::operator*(unsigned int val) const
    {
        return Time(m_min * val);
    }

    Time Time::operator /(unsigned int val)const
    {
        return Time(m_min / val);
    }

    Time Time::operator+(const Time& D)const
    {
        return Time(m_min + D.m_min);
    }

    Time Time::operator-(const Time& D)const
    {
        int start_time = (m_min % 1440);
        int end_time = (D.m_min % 1440);
        if (start_time < end_time)
            start_time += 1440;
        return Time(start_time - end_time);
    }

    Time& Time::operator*=(unsigned int val)
    {
        return *this = *this * val;
    }

    Time& Time::operator /= (unsigned int val)
    {
        return *this = *this / val;
    }

    Time& Time::operator+=(const Time& D)
    {
        return *this = *this + D;
    }

    Time& Time::operator-=(const Time& D)
    {
        return *this = *this - D;
    }

    Time::operator int() const
    {
        return (int)m_min;
    }

    Time::operator unsigned int() const
    {
        return m_min;
    }

    istream& operator>>(istream& str, Time& t)
    {
        return t.read(str);
    }

    ostream& operator<<(ostream& ostr, const Time& t)
    {
        return t.write(ostr);
    }
}
