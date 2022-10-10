/*  Dual Clock Display
 *  Author: Dante A. Trisciuzzi
 *  Date: 5.17.2022
 *  CS-210 Project 1
 *  SNHU | 22EW5 | Prof. Bill Chan
 */

#include "Menu.h"
#include "ConsoleHelpers.h"

using namespace ConsoleHelpers;

Menu::Menu() {
   // Initialize items list. For loops will still run fine if the list is left empty.
   items = {};
}

void Menu::AddItem(const std::string& displayName, const std::function<void()>& callback) {
   // No more characters available for menu selection
   if (this->index >= '9')
   {
      std::cout << "Too many items in list, no available characters." << std::endl;
      return;
   }

   // Add new item to the menu if char is available
   MenuItem item = {displayName, callback, this->index};
   items.emplace_back(item);


   // Increment char for menu.
   // Don't worry about going over 122 ('z') because exception is handled above.
   if (this->index < '9')
   {
      this->index += 1;
   }

}

void Menu::PrintMenu() const {
   // Print menu top bar
   PrintFill(TRIM_WIDTH + INTERIOR_PANEL_WIDTH / 2 + CLOCK_PANEL_GAP_WIDTH / 2, ' ');
   PrintFill((TRIM_WIDTH * 2) + INTERIOR_PANEL_WIDTH, '*');
   std::cout << std::endl;

   for (auto& item : items)
   {
      // Print item with trim
      PrintFill(TRIM_WIDTH + INTERIOR_PANEL_WIDTH / 2 + CLOCK_PANEL_GAP_WIDTH / 2, ' ');
      const std::string menuTag(1, item.menuChoice);
      PrintMenuInterior(menuTag + " - " + item.name);
      std::cout << std::endl;
   }

   // Print menu footer
   PrintFill(TRIM_WIDTH + INTERIOR_PANEL_WIDTH / 2 + CLOCK_PANEL_GAP_WIDTH / 2, ' ');
   PrintFill((TRIM_WIDTH * 2) + INTERIOR_PANEL_WIDTH, '*');
   std::cout << std::endl;
}

bool Menu::ProcessMenuChoice() const {
   // While there is characters in the queue, read them and execute
   // .. the corresponding menu item.

   // This also serves to empty unmatched characters from the stream
   // .. including newline characters, etc.

   // This could be improved by using a hashmap rather than looping through a vector of items
   // .. but for this scope, I think this solution is sufficient

   while (_kbhit())
   {
      const char c = static_cast<char>(_getch());

      for (auto& item : items)
      {
         if (c == item.menuChoice)
         {
            item.callback();
            return true; // Valid choice was made
         }
      }
   }
   return false; // No valid choice was made
}
