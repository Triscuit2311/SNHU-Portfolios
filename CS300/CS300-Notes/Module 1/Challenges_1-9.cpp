
/*
Author: Dante A. Trisciuzzi
Date: September 2022
Description: Challenges for CS300 (DSA)
*/

//1.9.1
// Append newValue to the end of vector tempReadings. 
// Ex: If newValue = 67, then tempReadings = {53, 57, 60} becomes {53, 57, 60, 67}. 

#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_ELEMENTS = 3;
   vector<int> tempReadings(NUM_ELEMENTS);
   int newValue;
   unsigned int i;

   for (i = 0; i < tempReadings.size(); ++i) {
      cin >> tempReadings.at(i);
   }

   cin >> newValue;

   /* Solution */
    tempReadings.push_back(newValue);
   /* End Solution */

   for (i = 0; i < tempReadings.size(); ++i) {
      cout << tempReadings.at(i) << " ";
   }
   cout << endl;

   return 0;
}

//1.9.2
//Remove the last element from vector ticketList. 
#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_ELEMENTS = 3;
   vector<int> ticketList(NUM_ELEMENTS);
   unsigned int i;

   for (i = 0; i < ticketList.size(); ++i) {
      cin >> ticketList.at(i);
   }

    /* Solution */
    ticketList.pop_back();
    /* End Solution */

   for (i = 0; i < ticketList.size(); ++i) {
      cout << ticketList.at(i) << " ";
   }
   cout << endl;

   return 0;
}

// 1.9.3
// Write a statement to print "Last mpg reading: " followed by the value of mpgTracker's last element.
// .. End with newline. Ex: If mpgTracker = {17, 19, 20}, print:

// Last mpg reading: 20
#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_ELEMENTS = 3;
   vector<int> mpgTracker(NUM_ELEMENTS);
   int i;

   for (i = 0; i < mpgTracker.size(); ++i) {
      cin >> mpgTracker.at(i);
   }

   /* Solution */
   cout << "Last mpg reading: " << mpgTracker.back() << endl;
   /* End Solution */

   return 0;
}