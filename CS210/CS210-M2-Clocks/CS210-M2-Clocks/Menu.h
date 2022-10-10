/*  Dual Clock Display
 *  Author: Dante A. Trisciuzzi
 *  Date: 5.17.2022
 *  CS-210 Project 1
 *  SNHU | 22EW5 | Prof. Bill Chan
 */

#pragma once
#include "Shared.h"


/**
 * \brief Simple console menu. Items execute callbacks when selected.
 * Only supports 9 items, to keep them tidy and on screen for the scope of this clocks project.
 */
class Menu {

   /**
     * \brief Struct containing data for a menu item.
     */
   struct MenuItem {
      std::string name;
      std::function<void()> callback;
      char menuChoice;
   };


   /**
     * \brief Vector of menuItem objects for iterating.
     */
   std::vector<MenuItem> items;

   char index = '1';

public:
   /**
     * \brief Initializes the class and the menu storage vector.
     */
   Menu();


   /**
     * \brief Adds an item to the menu.
     * \param displayName String to display in menu
     * \param callback Callback to execute when item is chosen.
     */
   void AddItem(const std::string& displayName, const std::function<void()>& callback);


   /**
     * \brief Prints menu to std::cout.
     */
   void PrintMenu() const;


   /**
     * \brief Empties input stream and executes callbacks for valid items.
     * \return True if valid choice is made, else false.
     */
   bool ProcessMenuChoice() const;
};
