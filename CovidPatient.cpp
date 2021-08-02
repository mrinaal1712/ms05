#include <iostream>
#include "CovidPatient.h"
using namespace std;

namespace sdds
{
    int nextCovidTicket = 1;
    char CovidPatient::type() const
    {
        return 'C';
    }
    CovidPatient::CovidPatient(): Patient(nextCovidTicket++)
    {}
    istream& CovidPatient::csvRead(istream& istr)
    {
        Patient::csvRead(istr);
        nextCovidTicket = Patient::number() + 1;
        istr.ignore();
        return istr;
    }
    ostream& CovidPatient::write(ostream& ostr) const
    {
        if(fileIO())
            return Patient::csvWrite(ostr);
        ostr << "COVID TEST\n";
        Patient::write(ostr);
        ostr << "\n";
        return ostr;
    }
    istream& CovidPatient::read(istream& istr)
    {
        return (Patient::fileIO()) ? csvRead(istr) : Patient::read(istr);
    }
}
