/*  Dual Clock Display
 *  Author: Dante A. Trisciuzzi
 *  Date: 5.17.2022
 *  CS-210 Project 1
 *  SNHU | 22EW5 | Prof. Bill Chan
 */

#include "Shared.h"
#include "Menu.h"
#include "ClockPanel.h"
#include "ConsoleHelpers.h"

int main(int argc, char** argv) {

   // I could not find an elegant way to get the local time zone
   // .. without using localtime(), which is considered unsafe since C++ 14.
   // C++ 20 Has a nice way of doing this, but since the scenario is
   // .. all about adhering to the ISO standard, I am using C++ 14.
   constexpr int timeZoneOffset = -4;


   // Initialize exit flag, clock display and menu
   bool userRequestsExit = false;
   auto clocks = ClockPanel(timeZoneOffset);
   auto clockMenu = Menu();

   // Setup menu items
   // Lambda callbacks makes it easy to capture instances of classes
   clockMenu.AddItem("Add One Hour",
                     [& clocks]() { clocks.clock.AddHour(); });
   clockMenu.AddItem("Add One Minute",
                     [& clocks]() { clocks.clock.AddMinute(); });
   clockMenu.AddItem("Add One Second",
                     [& clocks]() { clocks.clock.AddSecond(); });
   clockMenu.AddItem("Exit Program",
                     [& userRequestsExit]() { userRequestsExit = true; });


   // Turn off cursor so it is not flickering while re-drawing
   // Clear screen to remove prompt and keep things aligned
   ConsoleHelpers::ToggleConsoleCursor(false);
   ConsoleHelpers::ClearScreen();

   // Print the initial clock display and menu
   std::cout << "\n\n";
   clocks.PrintPanel();
   std::cout << "\n\n";
   clockMenu.PrintMenu();


   // Main feedback loop
   while (!userRequestsExit)
   {
      // I use a for loop so that the I/O response is better
      // .. I sleep the thread in 10ms intervals, 10ms x 100 = 1000ms = 1s
      // .. This means I can add once second each time the for loop ends
      // .. and be relatively close to real time ticking
      for (auto i = 0; i < 100; i++)
      {
         // Check if the user has given us input, and perform the correct callback
         if (clockMenu.ProcessMenuChoice())
         {
            // If user chose to exit, we can skip the rest of the loop
            if (userRequestsExit)
            {
               break;
            }

            // Update clocks if user added time
            clocks.ReDrawTimes();
         }

         // No platform-specific code needed here
         std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }

      // After ~one second we add a second to the clocks and re-draw them
      clocks.clock.AddSecond();
      clocks.ReDrawTimes();
   }

   // Restore console cursor and clear the screen
   // .. (resets the cursor position as well)
   ConsoleHelpers::ClearScreen();
   ConsoleHelpers::ToggleConsoleCursor(true);

   return 0;
}
