#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H
#include "Patient.h"
#include <iostream>
namespace sdds
{
    class TriagePatient: public Patient
    {
        char* m_symptoms;
    public:
        TriagePatient();
        ~TriagePatient();
        char type()const;
        istream& csvRead(istream& is);
        ostream& write(ostream& ostr)const;
        istream& read(istream& istr);
        ostream& csvWrite(ostream& ostr)const;
    };
}
#endif // !SDDS_TRIAGEPATIENT_H
