
/*
Author: Dante A. Trisciuzzi
Date: September 2022
Description: Challenges for CS300 (DSA)
*/

//1.10.1
// Write a loop that subtracts 1 from each element in lowerScores if the original element was greater than 0,
// .. and otherwise just assigns the element with 0. Ex: lowerScores = {5, 0, 2, -3} becomes {4, 0, 1, 0}. 
#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int SCORES_SIZE = 4;
   vector<int> lowerScores(SCORES_SIZE);
   unsigned int i;

   for (i = 0; i < lowerScores.size(); ++i) {
      cin >> lowerScores.at(i);
   }

   /* Solution */
   for(auto& n : lowerScores){
      n = n > 0 ? n - 1 : 0;
   }
   /* End Solution */

   for (i = 0; i < lowerScores.size(); ++i) {
      cout << lowerScores.at(i) << " ";
   }
   cout << endl;

   return 0;
}


//1.10.2
// Write a loop that sets newScores to oldScores shifted once left, with element 0 copied to the end.
// .. Ex: If oldScores = {10, 20, 30, 40}, then newScores = {20, 30, 40, 10}.

// Note: These activities may test code with different test values. This activity will perform two tests,
// .. both with a 4-element array. See "How to Use zyBooks".

// Also note: If the submitted code tries to access an invalid array element,
// .. such as newScores[9] for a 4-element array, the test may generate strange results.
// ..  Or the test may crash and report "Program end never reached", in which case the system
// ..   doesn't print the test case that caused the reported message. 
#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int SCORES_SIZE = 4;
   vector<int> oldScores(SCORES_SIZE);
   vector<int> newScores(SCORES_SIZE);
   unsigned int i;

   for (i = 0; i < oldScores.size(); ++i) {
      cin >> oldScores.at(i);
   }

   /* Solution */
   for (i = 0; i < oldScores.size(); ++i) {
      if(i < oldScores.size()-1){
         newScores.at(i) = oldScores.at(i+1);
         continue;
      }
      newScores.at(i) = oldScores.at(0);
   }
   /* End Solution */

   for (i = 0; i < newScores.size(); ++i) {
      cout << newScores.at(i) << " ";
   }
   cout << endl;

   return 0;
}

//1.10.3
// Write a loop that sets each vector element to the sum of itself and the next element,
// .. except for the last element which stays the same. Be careful not to index beyond the last element. Ex:

// Initial scores:        10, 20, 30, 40
// Scores after the loop: 30, 50, 70, 40

// The first element is 30 or 10 + 20, the second element is 50 or 20 + 30,
// .. and the third element is 70 or 30 + 40. The last element remains the same.
#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int SCORES_SIZE = 4;
   vector<int> bonusScores(SCORES_SIZE);
   unsigned int i;

   for (i = 0; i < bonusScores.size(); ++i) {
      cin >> bonusScores.at(i);
   }

   /* Solution */
   for (i = 0; i < bonusScores.size()-1; ++i) {
      bonusScores.at(i) += bonusScores.at(i+1); 
   }
   /* End Solution */

   for (i = 0; i < bonusScores.size(); ++i) {
      cout << bonusScores.at(i) << " ";
   }
   cout << endl;

   return 0;
}


//1.10.4
// Subtract 4 to any element's value that is greater than maxVal.
// .. Ex: If maxVal = 10, then dataPoints = {2, 12, 9, 20} becomes {2, 8, 9, 16}. 
#include <iostream>
#include <vector>
using namespace std;

int main() {
   int maxVal;
   const int NUM_POINTS = 4;
   vector<int> dataPoints(NUM_POINTS);
   unsigned int i;

   cin >> maxVal;

   for (i = 0; i < dataPoints.size(); ++i) {
      cin >> dataPoints.at(i);
   }

   /* Solution */
    for(auto& n : dataPoints){
    n -= n > maxVal ? 4 : 0;
    }
   /* End Solution */

   for (i = 0; i < dataPoints.size(); ++i) {
      cout << dataPoints.at(i) << " " ;
   }
   cout << endl;

   return 0;
}


// 1.10.5
// If the vector oldData is the same as the vector newData, print "Data matches!" ended with a newline.
// .. Otherwise, assign oldData with newData.
// .. Ex: If oldData = {10, 12, 18, 16} and newData = {25, 27, 29, 23}, then oldData becomes {25, 27, 29, 23}. 
#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_POINTS = 4;
   vector<int> oldData(NUM_POINTS);
   vector<int> newData(NUM_POINTS);
   unsigned int i;

   for (i = 0; i < oldData.size(); ++i) {
      cin >> oldData.at(i);
   }

   for (i = 0; i < newData.size(); ++i) {
      cin >> newData.at(i);
   }

   /* Solution */
   cout << (oldData == newData ? "Data matches!\n" : "");
   oldData = oldData == newData ? oldData : newData;
   /* End Solution */

   for (i = 0; i < oldData.size(); ++i) {
      cout << oldData.at(i) << " ";
   }
   cout << endl;

   return 0;

}