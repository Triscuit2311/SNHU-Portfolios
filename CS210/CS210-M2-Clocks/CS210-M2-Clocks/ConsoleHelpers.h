/*  Dual Clock Display
 *  Author: Dante A. Trisciuzzi
 *  Date: 5.17.2022
 *  CS-210 Project 1
 *  SNHU | 22EW5 | Prof. Bill Chan
 */

/*
 * ANSI Escape info from: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
 */

#pragma once
#include "Shared.h"


/**
 * \brief Some helpful functions for working with the console I/O. ANSI required.
 *  Tested on the Windows Terminal, ZSH, Kitty shell on Arch.
 */
namespace ConsoleHelpers {
   // Const variables for formatting
   constexpr int INTERIOR_PANEL_WIDTH = 24;
   constexpr int TRIM_WIDTH = 1;
   constexpr int CLOCK_PANEL_GAP_WIDTH = 6;


   /**
    * \brief Uses ANSI Escape sequence to toggle console cursor
    * \param useCursor true to enable cursor, false to disable.
    */
   inline void ToggleConsoleCursor(const bool useCursor) {
      std::cout << "\033[?25" << (useCursor ? 'H' : 'l') << std::flush;
   }


   /**
    * \brief Uses ANSI escape sequence to push output a page up and resets cursor.
    */
   inline void ClearScreen() {
      std::cout << "\033[2J\033[1;1H" << std::flush;
   }


   /**
    * \brief Uses ANSI escape sequence to reposition console cursor
    * \param x column to move to
    * \param y row to move to
    */
   inline void MoveConsoleCursorTo(const int x, const int y) {
      std::cout << "\033[" << y << ';' << x << 'H' << std::flush;
   }


   /**
    * \brief Uses ANSI escape sequence to save current position of cursor
    */
   inline void SaveConsoleCursorPos() {
      std::cout << "\033[s" << std::flush;
   }


   /**
    * \brief Uses ANSI escape sequence to restore cursor to last saved position.
    *  See SaveConsoleCursorPos().
    */
   inline void RestoreConsoleCursorPos() {
      std::cout << "\033[u" << std::flush;
   }


   /**
    * \brief Prints string centered in block to std::cout
    * \param width width of block
    * \param str string to center
    * \param fill fill character, defaults to a space
    */
   inline void PrintCentered(const int width, const std::string& str, const char fill = ' ') {
      const int edgeSize = (width - static_cast<int>(str.size())) / 2;

      std::cout << std::setfill(fill) << std::setw(width - edgeSize) <<
         str << std::setw(edgeSize) << "" << std::flush;
   }


   /**
    * \brief Prints filled block to std::cout
    * \param width width of block
    * \param fill fill character
    */
   inline void PrintFill(const int width, const char fill) {
      std::cout << std::setfill(fill) << std::setw(width) << "" << std::flush;
   }


   /**
    * \brief Prints a string centered in a trimmed block to std::cout
    * \param str string to print
    */
   inline void PrintMenuInterior(const std::string& str) {
      PrintFill(TRIM_WIDTH, '*');
      PrintCentered(INTERIOR_PANEL_WIDTH, str, ' ');
      PrintFill(TRIM_WIDTH, '*');
   }

}
