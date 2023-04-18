#include "HashTable.hpp"
#include <string>
#include <iostream>

using std::cout;
using std::endl;

HashTable::HashTable()
{
	this->nodes.resize(this->tableSize);
}

HashTable::HashTable(unsigned int size)
{
	this->tableSize = tableSize;
	this->nodes.resize(this->tableSize);
}

HashTable::~HashTable()
{
	this->nodes.erase(this->nodes.begin());
}

/// <summary>
/// Hashing based on the numeric part of the course id. Would be a collision if two courses have the same last 3 numbers
/// </summary>
/// <param name="courseId"></param>
/// <returns></returns>
unsigned int HashTable::Hash(string courseId)
{
	int key = std::stoi(courseId.substr(courseId.length() - 3));
	return key % this->tableSize;
}

/// <summary>
/// Insert course into the table
/// </summary>
/// <param name="course"></param>
void HashTable::Insert(Course course)
{
	unsigned hashKey = this->Hash(course.courseId);
	Node* curNode = &(this->nodes.at(hashKey));
	if (curNode == nullptr)
	{
		Node nodeToInsert = *(new Node(course, hashKey));
		this->nodes.insert(this->nodes.begin() + hashKey, nodeToInsert);
	}
	else if (curNode->key == UINT_MAX)
	{
		curNode->key = hashKey;
		curNode->course = course;
		curNode->next = nullptr;
	}
	else
	{
		while (curNode->next != nullptr)
		{
			curNode = curNode->next;
			curNode->next = new Node(course, hashKey);
		}
	}
}

/// <summary>
/// Print all courses
/// </summary>
void HashTable::PrintAll()
{
	for (int i = 0; i < this->nodes.size(); i++)
	{
		Node curNode = this->nodes.at(i);
		if (curNode.key != UINT_MAX)
		{
			curNode.course.Print();
		}
	}
}

/// <summary>
/// Find one course
/// </summary>
/// <param name="courseId"></param>
/// <returns></returns>
Course HashTable::Search(string courseId)
{
	Course course;

	// create the key for the given course
	unsigned hashKey = this->Hash(courseId);
	Node* node = &(this->nodes.at(hashKey));
	if (node != nullptr)
	{
		//return node course
		return node->course;
	}

	// if no entry found for the key
	if (node == nullptr)
	{
		return course;
	}

	while (node != nullptr)
	{
		// if the current node matches, return it
		if (node->course.courseId == courseId) {
			return node->course;
		}
		//node is equal to next node
		node = node->next;
	}
}