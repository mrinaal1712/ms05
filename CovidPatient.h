#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_
#include <iostream>
#include "Patient.h"

namespace sdds
{
    class CovidPatient: public Patient
    {
    public:
        CovidPatient();
        char type()const;
        istream& csvRead(istream& is);
        ostream& write(ostream& ostr)const;
        istream& read(istream& istr);
    };
}
#endif // !SDDS_COVIDPATIENT_H_
