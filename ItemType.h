/*
Author: John Lahut
Date: 12/22/2014
Project: HashTable
Filename: ItemType.h
Purpose: Provides the specification for an ItemType
*/

#include<string>

using namespace std;

typedef string DataType;

struct ItemType
{
	DataType data;		//Data being stored (hash key will be generated from this)
	int count;			//amount of times specific data occurs
};