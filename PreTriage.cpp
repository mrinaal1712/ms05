#include "PreTriage.h"
#include "utils.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;
namespace sdds
{
    PreTriage::PreTriage(const char* fn): m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
    m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2), m_avgCovidWait(15), m_avgTriageWait(5)
    {
        m_dataFilename = new char[strlen(fn)];
        strcpy(m_dataFilename, fn);
        load();
    }

    PreTriage::~PreTriage()
    {
        ofstream outFile(m_dataFilename);
        outFile << m_avgCovidWait << "," << m_avgTriageWait << "\n";
        cout << "Saving Average Wait Times,\n";
        cout << "\t" << "COVID Test: " << m_avgCovidWait << "\n";
        cout << "\t" << "Triage: " << m_avgTriageWait << "\n";

        for (int i = 0; i < m_lineupSize; i++)
        {
            m_linup[i]->fileIO(true);
            outFile << *m_linup[i] << endl;
            m_linup[i]->fileIO(false);
            cout << i + 1 << "- " << *m_linup[i] << endl;
        }
        outFile.close();
        for (int i = 0; i < m_lineupSize; i++)
            delete m_linup[i];
        delete[] m_dataFilename;
        cout << "done!\n";
    }

    const Time PreTriage::getWaitTime(const Patient& p) const
    {
        int count = 0;
        for (int i = 0; i < m_lineupSize; i++)
            if (p == *m_linup[i])
                count++;
        return (p.type() == 'C')? (m_avgCovidWait * count): (m_avgTriageWait * count);
    }

    void PreTriage::setAverageWaitTime(const Patient& p)
    {
        int AWT = (p.type() == 'C')? (int)m_avgCovidWait: (int)m_avgTriageWait;
        int CT = getTime();
        int PTT = (int)(Time)p;
        int PTN = p.number();
        AWT = ((CT - PTT)) + ((AWT * (PTN - 1))) / PTN;
        if (p.type() == 'C') m_avgCovidWait = AWT;
        else m_avgTriageWait = AWT;
    }

    void PreTriage::removePatientFromLineup(int index)
    {
        removeDynamicElement(m_linup, index, m_lineupSize);
    }

    int PreTriage::indexOfFirstInLine(char type)const
    {
        for (int i = 0; i < m_lineupSize; i++)
            if (*m_linup[i] == type)
                return i;
        return -1;
    }
    void PreTriage::load()
    {
        ifstream inFile;
        inFile.open(m_dataFilename, ifstream::in);
        cout << "Loading data...\n";
        m_lineupSize = 0;
        inFile >> m_avgCovidWait;
        inFile.ignore();
        inFile >> m_avgTriageWait;
        inFile.ignore();
        Patient* p = NULL;
        for (int i = 0; i < maxNoOfPatients; i++)
        {
            char c;
            inFile >> c;
            inFile.ignore();
            if (c == 'C') p = new CovidPatient();
            else if (c == 'T') p = new TriagePatient();
            if (p != NULL)
            {
                if (inFile.eof()) break;
                p->fileIO(true);
                inFile >> *p;
                p->fileIO(false);

                m_linup[i] = p;
                m_lineupSize++;
            }
        }
        if (!inFile.eof())
            cout << "Warning: number of records exceeded 100\n";
        if (m_lineupSize == 0)
        {
            cout << "No data or bad data file!\n";
            m_avgCovidWait = 15;
            m_avgTriageWait = 5;
        }
        else cout << m_lineupSize << " records imported...\n";
    }

    void PreTriage::reg()
    {
        if (m_lineupSize >= maxNoOfPatients)
        {
            cout << "Line up full!\n";
            return;
        }
        int selection;
        m_pMenu >> selection;
        if (selection == 1)
            m_linup[m_lineupSize++] = new CovidPatient();
        else if (selection == 2)
            m_linup[m_lineupSize++] = new TriagePatient();
        else if (selection == 0)
            return;
        m_linup[m_lineupSize - 1]->setArrivalTime();
        m_linup[m_lineupSize - 1]->fileIO(false);
        cout << "Please enter patient information: \n";
        cin >> *m_linup[m_lineupSize - 1];
        cout << "\n******************************************\n";
        cout << *m_linup[m_lineupSize - 1];
        cout << "Estimated wait time: " << getWaitTime(*m_linup[m_lineupSize - 1]);
        cout << "\n******************************************\n\n\n";
    }

    void PreTriage::admit()
    {
        int selection;
        m_pMenu >> selection;
        char type;
        if (selection == 1) type = 'C';
        else if (selection == 2) type = 'T';
        else if (selection == 0) return;
        int next_index = indexOfFirstInLine(type);
        if (next_index < 0) return;
        cout << "\n******************************************\n";
        m_linup[next_index]->fileIO(false);
        cout << "Calling for " << *m_linup[next_index];
        cout << "******************************************\n\n";
        setAverageWaitTime(*m_linup[next_index]);
        removePatientFromLineup(next_index);
    }

    void PreTriage::run()
    {
        while (1)
        {
            int sel;
            m_appMenu >> sel;
            if (sel == 0) return;
            else if (sel == 1) reg();
            else if (sel == 2) admit();
        }
    }
}
