#include "Patient.h"
#include "Time.h"
#include <iostream>
#include <iomanip>
#include "utils.h"
#include <cstring>
using namespace std;

namespace sdds
{

    Patient::~Patient()
    {
        delete[] m_patient_name;
    }

    int Patient::number() const
    {
        return m_ticket.number();
    }
    Patient::operator Time() const
    {
        return (Time) m_ticket;
    }

    bool Patient::fileIO() const
    {
        return m_fileIO_flag;
    }

    void Patient::fileIO(bool b)
    {
        m_fileIO_flag = b;
    }

    bool Patient::operator==(char ch) const
    {
        return ch == type();
    }

    bool Patient::operator==(const Patient& p) const
    {
        return type() == p.type();
    }

    void Patient::setArrivalTime()
    {
        m_ticket.resetTime();
    }

    ostream& Patient::csvWrite(ostream& ostr) const
    {
        ostr << type() << "," << m_patient_name << "," << m_OHIP_number << ",";
        m_ticket.csvWrite(ostr);
        return ostr;
    }

    istream& Patient::csvRead(istream& istr)
    {
        delete[] m_patient_name;
        m_patient_name = new char[30];
        istr.getline(m_patient_name, 25, ',');
        if (strlen(m_patient_name) == 1)
        {
            delete[] m_patient_name;
            string s;
            getline(istr, s, ',');
            string substr = s.substr(0, 25);
            m_patient_name = new char[substr.length()];
            strcpy(m_patient_name, substr.c_str());
        }
        istr >> m_OHIP_number;
        istr.ignore();
        m_ticket.csvRead(istr);
        return istr;
    }

    ostream& Patient::write(ostream& ostr) const
    {
        ostr <<  m_ticket << "\n";
        ostr << m_patient_name;
        ostr << ", OHIP: ";
        ostr << m_OHIP_number;
        return ostr;
    }

    int getInt(const char* prompt, istream& istr) {
       if (prompt != nullptr)
            cout << prompt << ": ";
        int input;
        istr >> input;
        while (!istr || istr.peek() != '\n') {

            if (istr) cout << "Enter only an Integer. Try again: ";
            else cout << "Bad Integer Value. Try again: ";
            istr.clear ();
            istr.ignore ( 100 , '\n' );
            istr >> input;
        }

        return input;
   }

   int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError, istream& istr) {
       int number = getInt(prompt, istr);
       while (number < min || number > max) {
            if (errorMessage != nullptr) {
                 cout << errorMessage << ": ";
            }
            if (showRangeAtError)
                cout << "[" << min << " <= Value <= " << max << "]: ";
            number = getInt(prompt, istr);
       }
       return number;
   }

    istream& Patient::read(istream& istr)
    {
        delete[] m_patient_name;
        m_patient_name = new char[30];
        cout << "Name: ";
        istr.getline(m_patient_name, 30);
        cout << "OHIP: ";
        m_OHIP_number = getInt(100000000, 999999999, nullptr,  "Invalid input ", true, istr);
        return istr;
    }
}
