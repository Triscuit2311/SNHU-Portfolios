/*
 * Dante Trisciuzzi
 * 10.10.2022
 * CS-300-T1157 SNHU
 * Prof. Dewin Andujar
 *
 * Project Two: ABCU Course Planner
 */

#pragma once
#include <string>
#include <vector>

struct Course
{
    std::string CourseNo;
    std::string Description;
    std::vector<std::string> Prerequisites;

    Course();
    Course(
        std::string course_no,
        std::string description,
        std::vector<std::string> prerequisites);

    bool operator < (const Course& rhs) const
    {
        return this->CourseNo < rhs.CourseNo;
    }

    void Print() const;
    void PrintPrerequisites() const;
};