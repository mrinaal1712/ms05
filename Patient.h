#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include "IOAble.h"
#include "Ticket.h"
#include <iostream>
namespace sdds
{
    class Patient: public IOAble
    {
        char* m_patient_name;
        int m_OHIP_number;
        Ticket m_ticket;
        bool m_fileIO_flag;
    public:
        Patient(int n=0, bool flag=false): m_ticket(n), m_fileIO_flag(flag)
        {
            m_patient_name = new char[30];
        }
        Patient(const Patient& p) = delete;
        Patient& operator=(const Patient& p) = delete;
        virtual ~Patient();

        virtual char type()const = 0;
        bool fileIO()const;
        void fileIO(bool b);
        bool operator==(char ch)const;
        bool operator==(const Patient& p)const;
        void setArrivalTime();
        operator Time()const;
        int number()const;
        ostream& csvWrite(ostream& os)const;
         istream& csvRead(istream& is) ;
       ostream& write(ostream& os)const;
        istream& read(istream& istr);
    };
}
#endif // PATIENT_H_INCLUDED
