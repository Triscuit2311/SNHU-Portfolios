
/*
Author: Dante A. Trisciuzzi
Date: September 2022
Description: Challenges for CS300 (DSA)
*/

// 1.6.2
// Assign numMatches with the number of elements in userValues that equal matchValue.
// .. userValues has NUM_VALS elements. Ex: If userValues is {2, 2, 1, 2} and matchValue is 2 ,
// .. then numMatches should be 3.

// Your code will be tested with the following values:
// * matchValue: 2, userValues: {2, 2, 1, 2} (as in the example program above)
// * matchValue: 0, userValues: {0, 0, 0, 0}
// * matchValue: 50, userValues: {10, 20, 30, 40} 

#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_VALS = 4;
   int matchValue;
   unsigned int i;
   int numMatches = -99; // Assign numMatches with 0 before your for loop
   vector<int> userValues(NUM_VALS);

   cin >> matchValue;

   for (i = 0; i < userValues.size(); ++i) {
      cin >> userValues.at(i);
   }

   /* Solution */
   numMatches = 0;
   for(auto& n : userValues){
      if(matchValue == n)
         numMatches++;
   }
   /* End Solution */

   cout << "matchValue: " << matchValue << ", numMatches: " << numMatches << endl;

   return 0;
}

// 1.6.3
// Write a for loop to populate vector userGuesses with NUM_GUESSES integers.
// .. Read integers using cin. Ex: If NUM_GUESSES is 3 and user enters 9 5 2, then userGuesses is {9, 5, 2}. 
#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_GUESSES = 3;
   vector<int> userGuesses(NUM_GUESSES);
   unsigned int i;

    /* Solution */
    for (i = 0; i < userGuesses.size(); ++i) {
        cin >> userGuesses.at(i);
    }
    /* End Solution */

   for (i = 0; i < userGuesses.size(); ++i) {
      cout << userGuesses.at(i) << " ";
   }

   return 0;
}

// 1.6.4
// Vector testGrades contains NUM_VALS test scores.
// .. Write a for loop that sets sumExtra to the total extra credit received.
// .. Full credit is 100, so anything over 100 is extra credit.
// .. Ex: If testGrades = {101, 83, 107, 90}, then sumExtra = 8, because 1 + 0 + 7 + 0 is 8. 

#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_VALS = 4;
   vector<int> testGrades(NUM_VALS);
   unsigned int i;
   int sumExtra = -9999; // Assign sumExtra with 0 before your for loop

   for (i = 0; i < testGrades.size(); ++i) {
      cin >> testGrades.at(i);
   }

   /* Solution */
   sumExtra = 0;
   for(auto& n : testGrades){
      if(n > 100)
         sumExtra += (n-100);
   }
   /* End Solution */

   cout << "sumExtra: " << sumExtra << endl;
   return 0;
}


// 1.6.5
// Write a for loop to print all NUM_VALS elements of vector hourlyTemp. 
// .. Separate elements with a comma and space. Ex: If hourlyTemp = {90, 92, 94, 95}, print:

// 90, 92, 94, 95

// Your code's output should end with the last element, without a subsequent comma, space, or newline. 
#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_VALS = 4;
   unsigned int i;
   vector<int> hourlyTemp(NUM_VALS);

   for (i = 0; i < hourlyTemp.size(); ++i) {
      cin >> hourlyTemp.at(i);
   }

   /* Solution */
   for (i = 0; i < hourlyTemp.size(); ++i) {
      cout << hourlyTemp.at(i) << (i == hourlyTemp.size()-1 ? "" : ", ");
   }  
   /* End Solution */

   cout << endl;

   return 0;
}
