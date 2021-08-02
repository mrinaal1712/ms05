#ifndef SDDS_PRETRIAGE_H_
#define SDDS_PRETRIAGE_H_
#include "Menu.h"
#include "Patient.h"
namespace sdds
{
    const int maxNoOfPatients = 100;
    class PreTriage
    {
        Time m_avgCovidWait, m_avgTriageWait;
        Patient* m_linup[maxNoOfPatients] {};
        char* m_dataFilename = nullptr;
        int m_lineupSize = 0;
        Menu m_appMenu, m_pMenu;
        void reg();
        void admit();
        const Time getWaitTime(const Patient& p)const;
        void setAverageWaitTime(const Patient& p);
        void removePatientFromLineup(int index);
        int indexOfFirstInLine(char type)const;
        void load();
   public:
        PreTriage(const char* dataFilename);
        ~PreTriage();
        void run(void);
    };
}

#endif // PRETRIAGE_H_INCLUDED
