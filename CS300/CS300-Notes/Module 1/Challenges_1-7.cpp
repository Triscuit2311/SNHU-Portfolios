

/*
Author: Dante A. Trisciuzzi
Date: September 2022
Description: Challenges for CS300 (DSA)
*/

// 1.7.1
// Add each element in origList with the corresponding value in offsetAmount.
// .. Print each sum followed by a space. Ex: If origList = {40, 50, 60, 70} and offsetAmount = {5, 7, 3, 0}, print:
// 45 57 63 70   
#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int NUM_VALS = 4;
   vector<int> origList(NUM_VALS);
   vector<int> offsetAmount(NUM_VALS);
   unsigned int i;

   for (i = 0; i < origList.size(); ++i) {
      cin >> origList.at(i);
   }

   for (i = 0; i < offsetAmount.size(); ++i) {
      cin >> offsetAmount.at(i);
   }

   /* Solution */
   for (i = 0; i < offsetAmount.size(); ++i) {
      cout << offsetAmount.at(i) + origList.at(i) << ' ';
   }
   /* End Solution */

   cout << endl;

   return 0;
}


//1.7.2
// For any element in keysList with a value greater than 100, print the corresponding value in itemsList,
// .. followed by a space. Ex: If keysList = {42, 105, 101, 100} and itemsList = {10, 20, 30, 40}, print:
// 20 30 
// Since keysList.at(1) and keysList.at(2) have values greater than 100, the value of itemsList.at(1)
// .. and itemsList.at(2) are printed. 
#include <iostream>
#include <vector>
using namespace std;

int main() {
   const int SIZE_LIST = 4;
   vector<int> keysList(SIZE_LIST);
   vector<int> itemsList(SIZE_LIST);
   unsigned int i;

   for (i = 0; i < keysList.size(); ++i) {
      cin >> keysList.at(i);
   }

   for (i = 0; i < itemsList.size(); ++i) {
      cin >> itemsList.at(i);
   }

   /* Solution */
   for (i = 0; i < keysList.size(); ++i) {
      if(keysList.at(i) > 100)
         cout << itemsList.at(i) << ' ';
   }
   /* End Solution */

   cout << endl;

   return 0;
}

