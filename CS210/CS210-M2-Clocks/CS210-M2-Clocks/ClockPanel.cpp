/*  Dual Clock Display
 *  Author: Dante A. Trisciuzzi
 *  Date: 5.17.2022
 *  CS-210 Project 1
 *  SNHU | 22EW5 | Prof. Bill Chan
 */

#include "ClockPanel.h"
#include "ConsoleHelpers.h"

using namespace ConsoleHelpers;

void ClockPanel::PrintDoubleInterior(const std::string& str1, const std::string& str2) {
   // Print two panels side-by-side, with a gap
   PrintMenuInterior(str1);
   PrintFill(CLOCK_PANEL_GAP_WIDTH, ' ');
   PrintMenuInterior(str2);
   std::cout << std::endl;
}

void ClockPanel::PrintClocksHeaderFooter() {
   // Print two headers, with a gap
   PrintFill((TRIM_WIDTH * 2) + INTERIOR_PANEL_WIDTH, '*');
   PrintFill(CLOCK_PANEL_GAP_WIDTH, ' ');
   PrintFill((TRIM_WIDTH * 2) + INTERIOR_PANEL_WIDTH, '*');
   std::cout << std::endl;
}

ClockPanel::ClockPanel(const int utcOffset) {
   clock = ClockPair(utcOffset);
}


void ClockPanel::PrintPanel() const {
   // Print the header and clock description
   PrintClocksHeaderFooter();
   PrintDoubleInterior("12-Hour clockPair", "24-Hour clockPair");

   // Save the cursor position at the beginning of the line that
   // .. we will be printing the clock times on.
   // .. This way, we can return to this position later
   // .. and only overwrite this single line
   SaveConsoleCursorPos();

   // Print the clock times
   PrintDoubleInterior(clock.Get12HTimeString(), clock.Get24HTimeString());

   // Print the footer
   PrintClocksHeaderFooter();
}

void ClockPanel::ReDrawTimes() const {
   // Return to the beginning of the line where we print the clock times
   // .. See PrintPanel()
   RestoreConsoleCursorPos();

   // Print the clock times
   PrintDoubleInterior(clock.Get12HTimeString(), clock.Get24HTimeString());
}
