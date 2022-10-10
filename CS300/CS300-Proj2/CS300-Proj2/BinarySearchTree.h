/*
 * Dante Trisciuzzi
 * 10.10.2022
 * CS-300-T1157 SNHU
 * Prof. Dewin Andujar
 *
 * Project Two: ABCU Course Planner
 */

#pragma once
#include <functional>
#include <utility>
#include "Course.h"


// Define Node structure
struct Node
{
	Course course;
	Node* left;
	Node* right;

	Node()
	{
		this->course = Course();
		left = nullptr;
		right = nullptr;
	}

	explicit Node(Course course)
	{
		this->left = nullptr;
		this->right = nullptr;
		this->course = std::move(course);
	}
};


class BinarySearchTree final
{
public:
	enum Order
	{
		IN_ORDER,
		PRE_ORDER,
		POST_ORDER
	};

	BinarySearchTree();
	virtual ~BinarySearchTree();

	// Copy Constructors
	BinarySearchTree(const BinarySearchTree& tree);
	BinarySearchTree& operator=(const BinarySearchTree& rhs);

	// Move Constructors
	BinarySearchTree(const BinarySearchTree&& tree) noexcept;
	BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept;

	// Essential Operations
	void Insert(Course course);
	void Remove(const std::string& course_id);
	Course Search(const std::string& course_id) const;
	void Print(Order order = IN_ORDER) const;

	// Helpful Extra Methods
	size_t Size() const;
	void Clear();
	void ForEach(const std::function<void(Node*)>& func) const;
	bool Contains(const std::string& course_id) const;

private:
	// Mutable for assignment via move constructors
	mutable Node* root_;

	size_t size_ = 0;

	Node* RemoveNode(Node* node, const std::string& course_id);

	// Since none of these methods require instance specific
	// .. variables, we can make them static
	static void AddNode(Node* node, const Course& course);
	static void DeleteNodeRecursive(const Node* node);
	static void InOrder(Node* node);
	static void PostOrder(Node* node);
	static void PreOrder(Node* node);
	static void InOrderIteration(Node* node, const std::function<void(Node*)>& func);
};
