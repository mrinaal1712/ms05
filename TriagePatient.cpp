#include "TriagePatient.h"
#include "utils.h"
using namespace std;

namespace sdds {
   int nextTriageTicket = 1;

   TriagePatient::TriagePatient(): Patient(nextTriageTicket++)
   {
       m_symptoms = NULL;
   }
   TriagePatient::~TriagePatient()
   {
       delete[] m_symptoms;
   }
   char TriagePatient::type()const
   {
       return 'T';
   }

   ostream& TriagePatient::csvWrite(ostream& ostr) const
   {
       Patient::csvWrite(ostr);
       return ostr << "," << m_symptoms;
   }
   istream& TriagePatient::csvRead(istream& istr)
   {
       delete[] m_symptoms;
       Patient::csvRead(istr);
       istr.ignore();
       m_symptoms = getcstr(nullptr, istr, '\n');
       nextTriageTicket = Patient::number() + 1;
       return istr;
   }

   ostream& TriagePatient::write(ostream& ostr)const
   {
       if (Patient::fileIO())
            return csvWrite(ostr);
       ostr << "TRIAGE\n";
       Patient::write(ostr);
       return ostr << "\nSymptoms: " << m_symptoms << "\n";
   }

   istream& TriagePatient::read(istream& istr)
   {
       if (Patient::fileIO())
            return csvRead(istr);
       delete[] m_symptoms;
       Patient::read(istr);
       cout << "Symptoms: ";
       m_symptoms = getcstr(nullptr, istr, '\n');
       return istr;
   }
}
