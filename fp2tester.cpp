// Final Project Tester
// file: fp2Tester.cpp
// Version: 1.0
// Date: 2021-06-23
// Author: Fardad
// Description:
// This file tests the Final project
// overall functionality
/////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include "PreTriage.h"
#include "utils.h"

using namespace sdds;
using namespace std;

void displayFile(const char* fname) {
   ifstream fin(fname);
   char ch;
   cout << endl << "******  Content of file: \"" << fname << "\":" << endl;
   while (fin.get(ch)) cout << ch;
   cout << "***************************************************" << endl << endl;
}
void copyFile(const char* des, const char* src) {
   ifstream s(src);
   ofstream d(des);
   char ch = 0;
   while (s.get(ch) && d << ch);
}
int main() {
   sdds::debug = true;
   copyFile("smalldata.csv.bak", "smalldata.csv");
   PreTriage P("smalldata.csv");
   P.run();
   return 0;
}