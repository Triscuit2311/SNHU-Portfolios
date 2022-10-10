/*  Dual Clock Display
 *  Author: Dante A. Trisciuzzi
 *  Date: 5.17.2022
 *  CS-210 Project 1
 *  SNHU | 22EW5 | Prof. Bill Chan
 */

#pragma once
#include "ClockPair.h"
#include "Shared.h"

class ClockPanel {

   /**
    * \brief Prints two menu panels with a separating gap to std::cout.
    * \param str1 String for first panel.
    * \param str2 String for second panel.
    */
   static void PrintDoubleInterior(const std::string& str1, const std::string& str2);


   /**
    * \brief Prints two asterisks blocks to act as a header/footer for dual menu panels.
    */
   static void PrintClocksHeaderFooter();

public:
   ClockPair clock;


   /**
    * \brief Constructor that uses no timezone offset. (UTC time)
    */
   ClockPanel() : ClockPanel(0) {
   }

   /**
    * \brief Constructor that uses timezone offset.
    * \param utcOffset Local timezone offset from UTC.
    */
   explicit ClockPanel(int utcOffset);


   /**
     * \brief Prints the clock panel to std::cout.
     * Warning: Overwrites saved cursor position.
     */
   void PrintPanel() const;


   /**
    * \brief Re-Draws the single line containing the clock times.
    * Warning: Moves cursor to last-saved cursor position.
    */
   void ReDrawTimes() const;
};
