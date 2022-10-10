/*  Dual Clock Display
 *  Author: Dante A. Trisciuzzi
 *  Date: 5.17.2022
 *  CS-210 Project 1
 *  SNHU | 22EW5 | Prof. Bill Chan
 */

#pragma once
#include "Shared.h"

/**
 * \brief struct for managing a pair of clocks (12 and 24 hour).
 * Based on a UNIX timestamp.
 */

struct ClockPair {
   /**
  * \brief Constructor with no timezone offset. (UTC time)
  */
   ClockPair() : ClockPair(0) {
   }


   /**
    * \brief Constructor with timezone offset
    * \param utcOffset Timezone offset from UTC.
    */
   explicit ClockPair(const int utcOffset) {
      this->unixTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
      this->unixTime += static_cast<std::time_t>(utcOffset) * 3600;
      this->UpdateTime();
   }


   /**
    * \brief Convert clockPair's time to a 24hr format.
    * \return string in HH:MM:SS format.
    */
   std::string Get24HTimeString() const {
      return std::to_string(this->hours) + ':'
         + (this->minutes < 10 ? "0" : "") + std::to_string(this->minutes) + ':'
         + (this->seconds < 10 ? "0" : "") + std::to_string(this->seconds);
   }


   /**
    * \brief Convert clockPair's time to a 12hr format.
    * \return string in HH:MM:SS AM/PM format.
    */
   std::string Get12HTimeString() const {
      const bool isAM = this->hours < 12;
      const unsigned long long hour = (this->hours > 12 ? this->hours - 12 : this->hours);

      return std::to_string(hour == 0 ? 12 : hour) + ':'
         + (this->minutes < 10 ? "0" : "") + std::to_string(this->minutes) + ':'
         + (this->seconds < 10 ? "0" : "") + std::to_string(this->seconds) + (isAM ? " AM" : " PM");
   }


   /**
    * \brief Adds one second to the internal clock
    */
   void AddSecond() {
      this->unixTime += 1;
      this->UpdateTime();
   }


   /**
  * \brief Adds one minute to the internal clock
  */
   void AddMinute() {
      this->unixTime += 60;
      this->UpdateTime();
   }


   /**
  * \brief Adds one hour to the internal clock
  */
   void AddHour() {
      this->unixTime += 3600;
      this->UpdateTime();
   }

private:
   std::time_t unixTime;
   unsigned long long seconds = 0;
   unsigned long long minutes = 0;
   unsigned long long hours = 0;


   /**
    * \brief Converts the internal UNIX timestamp to hours, minutes, and seconds (24HR format).
    */
   void UpdateTime() {
      this->hours = ((this->unixTime % 86400) / 3600);
      this->minutes = (this->unixTime % 3600) / 60;
      this->seconds = (this->unixTime % 60);
   }
};
