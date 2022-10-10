/*
 * Dante Trisciuzzi
 * 10.10.2022
 * CS-300-T1157 SNHU
 * Prof. Dewin Andujar
 *
 * Project Two: ABCU Course Planner
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BinarySearchTree.h"

// Uncomment to see courses being removed during prerequisite check
//#define USE_DEBUG_OUTPUT

// Defined below
int MainMenu(BinarySearchTree& tree);

int main()
{
	BinarySearchTree course_tree;

	while (MainMenu(course_tree) != 9) {}

	return 0;
}



/**
 * \brief Parses CSV and populates BST with course data
 * \param tree BST to populate
 * \param file_name CSV path
 */
void ParseCourseCsv(BinarySearchTree& tree, const std::string& file_name)
{
	auto in_file = std::ifstream(file_name);

	for (std::string line; getline(in_file, line);)
	{
		// Add a delimiter so we get the last token
		constexpr char delimiter = ',';
		line += delimiter;

		// Vars for token parsing
		size_t position;
		std::string token;

		// Default Constructor sets CourseID and Description to "None"
		auto course = Course();
		unsigned int i = 0;

		//While we have another delimiter in the line
		while ((position = line.find(delimiter)) != std::string::npos)
		{
			// Create a substring as a token
			token = line.substr(0, position);

			// Set course data based on token
			switch (i)
			{
			case 0:
				course.CourseNo = token;
				break;
			case 1:
				course.Description = token;
				break;
			default:
				course.Prerequisites.push_back(token);
			}
			i++;


			// Erase line up to current delimiter
			// .. So we do not keep getting the same token
			line.erase(0, position + 1);
		}

		// Insert new course into tree
		tree.Insert(course);
	}
}


/**
 * \brief Removes courses from tree if they are missing required pre-requisites
 * \param tree Binary Tree target
 */

void CheckPreRequisiteCourses(BinarySearchTree& tree)
{
	// Vector to hold courses that are missing pre-requisites
	std::vector<std::string> courses_to_remove;

	// We continue checking courses until no courses
	// .. with missing requirements remain in the tree
	// This is necessary because a course may be removed
	// .. that cleared another course as valid.
	while (true) {

		// Clear courses from last iteration
		courses_to_remove.clear();

		// Queue courses missing requirements for removal
		// .. lambda function pushes bad courses to removal vector
		tree.ForEach([&tree, &courses_to_remove](Node* node)
			{
				for (auto& s : node->course.Prerequisites)
				{
					if (!tree.Contains(s))
					{
						courses_to_remove.emplace_back(node->course.CourseNo);
						break;
					}
				}
			}
		);

		// If no courses are missing requirements, return
		if (courses_to_remove.empty())
			return;

		// Remove courses
#ifdef USE_DEBUG_OUTPUT
		std::cout << "Courses missing Pre-Requisites:\n";
#endif
		for (auto c : courses_to_remove)
		{
			tree.Remove(c);
#ifdef USE_DEBUG_OUTPUT
			std::cout << '\t' << c << " [Removed] " << std::endl;
#endif
		}
	}
}

// Escape sequence to push output up and reset cursor (Pseudo-ClearScreen)
void AnsiClearScreen() {
	std::cout << "\033[2J\033[1;1H" << std::flush;
}

/**
 * \brief Main menu for UI
 * \param tree BST for operations
 * \return user choice; 9 is exit
 */
int MainMenu(BinarySearchTree& tree)
{
	// Setup
	int choice = 0;
	std::string input_id;
	Course result_course;

	// Show options
	std::cout <<
		"\nMenu:\n" <<
		"  1. Load Data Structure\n"	<<
		"  2. Print Course List\n"	<<
		"  3. Print Course\n"			<<
		"  9. Exit\n" << 
		"> ";

	// Get user choice
	std::cin >> choice;

	AnsiClearScreen();

	// Execute appropriate option based on user choice
	switch(choice)
	{
	case 1:
		// Clear and populate BST
		tree.Clear();
		ParseCourseCsv(tree, "courselist.csv");
		CheckPreRequisiteCourses(tree);
		std::cout << "Courses loaded!" << std::endl;
		break;
	case 2:
		// Print Tree (Defaults to InOrder traversal)
		if(tree.Size() <= 0)
			std::cout << "No courses loaded." << std::endl;
		tree.Print();
		break;
	case 3:
		// Get Course ID from user
		std::cout << "Enter course ID: ";
		std::cin >> input_id;

		// Print search result
		result_course = tree.Search(input_id);
		if(result_course.CourseNo == "NONE")
		{
			std::cout << "Course not found." << std::endl;
			break;
		}
		result_course.PrintPrerequisites();
		break;
	case 9: 
		// breaks to return 9, main(...) will terminate loop
		break;
	default:
		std::cout << "Invalid choice." << std::endl;
		break;
	}

	// Clear and ignore input
	std::cin.clear();
	std::cin.ignore();
	return choice;
}
