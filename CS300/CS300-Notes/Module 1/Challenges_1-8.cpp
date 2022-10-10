
/*
Author: Dante A. Trisciuzzi
Date: September 2022
Description: Challenges for CS300 (DSA)
*/

//1.8.1
//Assign currentSize with the size of the sensorReadings vector. 
#include <iostream>
#include <vector>
using namespace std;

int main() {
   vector<int> sensorReadings(4);
   int currentSize;
   int input;
   cin >> input;

   sensorReadings.resize(input);

   /* Solution */
   currentSize = sensorReadings.size();
   /* End Solution */

   cout << "Number of elements: " << currentSize << endl;

   return 0;
}

//1.8.2
// Resize vector countDown to have newSize elements. 
// .. Populate the vector with integers {newSize, newSize - 1, ..., 1}. 
// .. Ex: If newSize = 3, then countDown = {3, 2, 1}, and the sample program outputs:
// 3 2 1 Go!
#include <iostream>
#include <vector>
using namespace std;

int main() {
   vector<int> countDown(0);
   int newSize;
   unsigned int i;

   cin >> newSize;

   /* Solution */
   countDown.resize(newSize);
   for(auto& n : countDown){
      n = newSize;
      newSize--;
   }
   /* End Solution */

   for (i = 0; i < countDown.size(); ++i) {
      cout << countDown.at(i) << " ";
   }
   cout << "Go!" << endl;

   return 0;
}

