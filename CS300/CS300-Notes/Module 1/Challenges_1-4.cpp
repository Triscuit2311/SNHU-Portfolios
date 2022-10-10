
/*
Author: Dante A. Trisciuzzi
Date: September 2022
Description: Challenges for CS300 (DSA)
*/

// 1.4.2
// Write three statements to print the first three elements of vector runTimes. Follow each with a newline.
#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_VALS = 5;
   vector<int> runTimes(NUM_VALS);
   unsigned int i;

   // Populate vector
   for (i = 0; i < runTimes.size(); ++i) {
      cin >> runTimes.at(i);
   }

   /* Solution */
   for (i = 0; i < 3; ++i) {
      cout << runTimes.at(i) << endl;
   }
   /* End Solution */

   return 0;
}

// 1.4.3
// Write a for loop to print all NUM_VALS elements of vector courseGrades, 
// .. following each with a space (including the last). Print forwards, then backwards. End with newline.

#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_VALS = 4;
   vector<int> courseGrades(NUM_VALS);
   int i;

   for (i = 0; i < courseGrades.size(); ++i) {
      cin >> courseGrades.at(i);
   }

   /* Solution */
   for(auto& n : courseGrades){
      cout << n << ' ';
   }
   cout << endl;
   
   for( i = courseGrades.size()-1; i >= 0; i--){
      cout << courseGrades[i] << ' ';
   }
   cout << endl;
   /* End Solution */

   return 0;
}

