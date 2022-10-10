/*
 * Dante Trisciuzzi
 * 10.10.2022
 * CS-300-T1157 SNHU
 * Prof. Dewin Andujar
 *
 * Project Two: ABCU Course Planner
 */

#include "BinarySearchTree.h"
#include <iostream>

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree()
{
	// Initialize root node to null
	this->root_ = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree()
{
	// initiate recursive delete
	DeleteNodeRecursive(this->root_);
}

/**
 * \brief Removes all nodes from the tree.
 */
void BinarySearchTree::Clear()
{
	while (this->root_ != nullptr)
		this->Remove(this->root_->course.CourseNo);
}


void BinarySearchTree::ForEach(const std::function<void(Node*)>& func) const
{
	InOrderIteration(this->root_, func);
}

size_t BinarySearchTree::Size() const
{
	return this->size_;
}

bool BinarySearchTree::Contains(const std::string& course_id) const
{
	return Search(course_id).CourseNo != "NONE";
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course)
{
	// Base case if there is no tree yet
	if (this->root_ == nullptr)
	{
		// Since course is passed by value, we move it into Node constructor
		this->root_ = new Node(std::move(course));
		return;
	}

	AddNode(this->root_, course);
	this->size_++;
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(const std::string& course_id)
{
	// Call private member function
	RemoveNode(this->root_, course_id);
	this->size_--;
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(const std::string& course_id) const
{
	// Set current node starting at root
	auto current_node = this->root_;

	// While we traverse to a valid node
	while (current_node != nullptr)
	{
		// If this is the node we want, return it
		if (course_id == current_node->course.CourseNo)
			return current_node->course;

		// Check the direction to traverse next
		if (course_id < current_node->course.CourseNo)
		{
			current_node = current_node->left;
		}
		else
		{
			current_node = current_node->right;
		}
	}

	// Return null course otherwise
	return {};
}

/**
 * \brief Print the entire Binary Tree Contents In/Pre/Post-Ordered
 * \param order Order of printed Nodes
 */
void BinarySearchTree::Print(const Order order) const
{
	switch (order)
	{
	case Order::IN_ORDER:
		InOrder(this->root_);
		break;
	case Order::PRE_ORDER:
		PreOrder(this->root_);
		break;
	case Order::POST_ORDER:
		PostOrder(this->root_);
		break;
	}
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course to be added
 */
void BinarySearchTree::AddNode(Node* node, const Course& course)
{
	// Set current node
	auto current_node = node;

	// We do not need a break condition
	// Since we return from the loop upon insertion
	while (true)
	{
		// If new node should be left of current
		if (course.CourseNo < current_node->course.CourseNo)
		{
			// If left is open, insert node
			if (current_node->left == nullptr)
			{
				current_node->left = new Node(course);
				return;
			}

			// Left not open, traverse to next node
			current_node = current_node->left;
			continue;
		}

		// New node should be right of current
		// If left is open, insert new node
		if (current_node->right == nullptr)
		{
			current_node->right = new Node(course);
			return;
		}

		// Right not open, traverse to next node
		current_node = current_node->right;
	}
}

void BinarySearchTree::InOrderIteration(Node* node, const std::function<void(Node*)>& func)
{
	// If we reach a null node, do nothing
	// This means we stop recursive calls from this node
	if (node == nullptr)
		return;

	// Recursive call left
	InOrderIteration(node->left, func);

	// Print node info
	func(node);

	// Recursive call right
	InOrderIteration(node->right, func);
}

Node* BinarySearchTree::RemoveNode(Node* node, const std::string& course_id)
{

	// Setup current and parent node pointers
	auto current_node = node;
	Node* parent_node = nullptr;

	// Traverse nodes
	while (current_node != nullptr)
	{
		// Found correct node
		if (course_id == current_node->course.CourseNo)
		{
			// Node is a leaf
			if (current_node->left == nullptr && current_node->right == nullptr)
			{
				// Current node is root
				if (parent_node == nullptr)
				{
					this->root_ = nullptr;
					return current_node;
				}

				// Current node is left of parent
				if (parent_node->left == current_node)
				{
					parent_node->left = nullptr;
					return current_node;
				}

				// Current node is right of parent
				if (parent_node->right == current_node)
				{
					parent_node->right = nullptr;
					return current_node;
				}
			}

			// Node only has left child
			if (current_node->right == nullptr)
			{
				// Current node is root
				if (parent_node == nullptr)
				{
					this->root_ = current_node->left;
					return current_node;
				}

				// Current node is left of parent
				if (parent_node->left == current_node)
				{
					parent_node->left = current_node->left;
					return current_node;
				}

				// Current node is right of parent
				if (parent_node->right == current_node)
				{
					parent_node->right = current_node->left;
					return current_node;
				}
			}

			// Node only has right child
			if (current_node->left == nullptr)
			{
				// Current node is root
				if (parent_node == nullptr)
				{
					this->root_ = current_node->right;
					return current_node;
				}

				// Current node is left of parent
				if (parent_node->left == current_node)
				{
					parent_node->left = current_node->right;
					return current_node;
				}

				// Current node is right of parent
				if (parent_node->right == current_node)
				{
					parent_node->right = current_node->right;
					return current_node;
				}
			}

			// Node has two children

			// Find successor (leftmost node in right child path)
			auto successor = current_node->right;
			while (successor->left != nullptr)
				successor = successor->left;

			// Store course
			const Course successorCourse = successor->course;

			// Recursively remove successor node
			RemoveNode(current_node, successor->course.CourseNo);

			// Store course to return
			const auto retCourse = current_node->course;

			// Set new node information to successor
			current_node->course = successorCourse;

			// Return a new node pointer
			return new Node(retCourse);
		}

		// Node not found this iteration
		if (course_id >= current_node->course.CourseNo)
		{
			parent_node = current_node;
			current_node = current_node->right;
			continue;
		}

		parent_node = current_node;
		current_node = current_node->left;
	}
	return {};
}

void BinarySearchTree::DeleteNodeRecursive(const Node* node)
{
	if (node == nullptr)
		return;
	DeleteNodeRecursive(node->left);
	DeleteNodeRecursive(node->right);
	delete node;
}

void BinarySearchTree::InOrder(Node* node)
{
	// If we reach a null node, do nothing
	// This means we stop recursive calls from this node
	if (node == nullptr)
		return;

	// Recursive call left
	InOrder(node->left);

	// Print node info
	node->course.Print();

	// Recursive call right
	InOrder(node->right);
}

void BinarySearchTree::PostOrder(Node* node)
{
	// If we reach a null node, do nothing
	// This means we stop recursive calls from this node
	if (node == nullptr)
		return;

	// Recursive call left
	InOrder(node->left);

	// Recursive call right
	InOrder(node->right);

	// Print node info
	node->course.Print();
}

void BinarySearchTree::PreOrder(Node* node)
{
	// if we reach a null node, do nothing
	// This means we stop recursive calls from this node
	if (node == nullptr)
		return;

	// Print node info
	node->course.Print();

	// Recursive call left
	InOrder(node->left);

	// Recursive call right
	InOrder(node->right);
}

