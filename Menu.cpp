#include "Menu.h"
#include "utils.h"
#include <iostream>
#include <cstring>
using namespace std;
namespace sdds
{
    Menu::Menu(const char* MenuContent, int NoOfSelections)
    {
        m_noOfSel = NoOfSelections;
        m_text = new char[strlen(MenuContent)];
        strcpy(m_text, MenuContent);
    }

    Menu::Menu(const Menu &m)
    {
        m_noOfSel = m.m_noOfSel;
        m_text = new char[strlen(m.m_text)];
        strcpy(m_text, m.m_text);
    }


    Menu::~Menu()
    {
        delete[] m_text;
    }

    void Menu::display()const
    {
        cout << m_text << endl;
        cout << "0-Exit" << endl;
    }

    int& Menu::operator>>(int& Selection)
    {
        display();
        Selection = getInt(0, m_noOfSel, "", "Value outside range", true);
        return Selection;
    }
}
