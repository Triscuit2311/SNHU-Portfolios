/*
 * Dante Trisciuzzi
 * 10.10.2022
 * CS-300-T1157 SNHU
 * Prof. Dewin Andujar
 *
 * Project Two: ABCU Course Planner
 */

#include "Course.h"
#include <iostream>
#include <utility>

Course::Course()
{
	this->CourseNo = "NONE";
	this->Description = "NONE";
	this->Prerequisites = {};
}

Course::Course(
	std::string course_no,
	std::string description,
	std::vector<std::string> prerequisites)
{
	this->CourseNo = std::move(course_no);
	this->Description = std::move(description);
	this->Prerequisites = std::move(prerequisites);
}

void Course::Print() const
{
	std::cout << this->CourseNo << ": " << this->Description << std::endl;
}

void Course::PrintPrerequisites() const
{
	std::cout << this->CourseNo <<
		"\n\tDescription: " << this->Description <<
		"\n\tPrerequisites: ";

	if (Prerequisites.empty())
	{
		std::cout << "None" << std::endl;
		return;
	}

	for (auto& s : Prerequisites)
		std::cout << s << " ";

	std::cout << std::endl;
}
