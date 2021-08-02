#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
   bool debug = false;  // made global in utils.h
   int getTime() {
      int mins = -1;
      if (debug) {
         Time t(0);
         cout << "Enter current time: ";
         do {
            cin.clear();
            cin >> t;   // needs extraction operator overloaded for Time
            if (!cin) {
               cout << "Invlid time, try agian (HH:MM): ";
               cin.clear();
            }
            else {
               mins = int(t);
            }
            cin.ignore(1000, '\n');
         } while (mins < 0);
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }

   int getInt(const char* prompt) {
       if (prompt != nullptr)
            cout << prompt << ": ";
        int input;
        cin >> input;
        while (!cin || cin.peek() != '\n') {

            if (cin) cout << "Enter only an Integer. Try again: ";
            else cout << "Bad Integer Value. Try again: ";
            cin.clear ();
            cin.ignore ( 100 , '\n' );
            cin >> input;
        }

        return input;
   }

   int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError) {
       int number = getInt(prompt);
       while (number < min || number > max) {
            if (errorMessage != nullptr) {
                 cout << errorMessage << ": ";
            }
            if (showRangeAtError)
                cout << "[" << min << " <= Value <= " << max << "]: ";
            number = getInt(prompt);
       }
       return number;
   }

   char* getcstr(const char* prompt, std::istream& istr, char delimiter)
   {
        if (prompt != nullptr)
            cout << prompt << ": ";
        string s;
        istr.ignore();
        getline(istr, s, delimiter);
        //cout << ".......AFTER GETLINE.........\n";
        int n = s.length();
        char* ch = new char[n];
        strcpy(ch, s.c_str());
        return ch;
   }

}
