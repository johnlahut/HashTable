/*
Author: John Lahut
Date: 12/22/2014
Project: HashTable
Filename: HashTable.h
Purpose: Provides the specification for an array based ADT HashTable
Assumptions: BUCKET_SIZE > 0 (bucket size of 1 is equivalent to not having a bucket)
IPO: Defined in .cpp
*/


#include "ItemType.h"

//Named constants

const int MAX_ELEMENTS = 500;	// <---- CHANGE TABLE SIZE HERE  (68 gets me to a occupancy of 80%)
const int BUCKET_SIZE = 6;		// <---- CHANGE BUCKET SIZE HERE

const string EMPTY_DATA = "";
const string EMPTY_PRINT = "--EMPTY--";
const string DOUBLE_TAB = "\t\t";

//Bucket size is always +1 (ex. BUCKET_SIZE = 6 ... the element plus its buckets (5) add up to 6 



const int ARRAY_SIZE = MAX_ELEMENTS*BUCKET_SIZE; // Do not modify

class HashTable
{

public:

	/***********************************************************************************************/

	//pre:	none		
	//post: a new HashTable object has been created and all PDM's have been instantiated
	HashTable();

	/***********************************************************************************************/

	//pre:	object has been instantiated
	//post:	returns the element denoted by currPos to the caller
	ItemType Retrieve() const;

	/***********************************************************************************************/

	//pre:	object has been instantiated
	//		item is a valid ItemType with initalized values
	//post: item has been inserted into the current object
	void Insert(/*in*/ItemType item);

	/***********************************************************************************************/

	//pre:	object has been instantiated
	//post:	returns true to the caller if currPos is at the end of the list, false otherwise
	bool EndOfList() const;

	/***********************************************************************************************/

	//pre:	object has been instantiated 
	//post:	sets the current position of the list to the first element
	void FirstPosition();

	/***********************************************************************************************/

	//pre:	object has been instantiated, not at the end of the list
	//post:	sets the current position of the list to the next position in the list
	void NextPosition();

	/***********************************************************************************************/


	/*      THESE PUBLIC METHODS ARE FOR DATA ANALYSIS/HASH FUNCTION ANALYSIS  */


	//pre:	object has been instantiated
	//post:	returns the number of initial collisions the hash table has encountered
	//		an initial collision occurs when a unique key is being inserted to the table that hashes to the same
	//		value as a pre-existing unique key
	int GetNumCollisions() const;

	/***********************************************************************************************/

	//pre:	object has been instantiated
	//post:	return the number of unique elements inserted into the hash table (number of elements in the table)
	int GetLength() const;

	/***********************************************************************************************/

	//pre:	object has been instantiated
	//post:	returns the number of duplicate elements encountered
	int GetDuplicates() const;

	//pre:	object has been instantiated
	//post:	returns the number of subsequent collisions the hash table has encountered
	//		a subsequent collision occurs when the CRP is in effect, and during this time the element that is 
	//		being inserted encounters a collision. In this specific case, if the first bucket spot is not open, that is
	//		a subsequent collision
	int GetSubsCollisions() const;

	/***********************************************************************************************/

	//pre:	object has been instantiated
	//post:	returns the percentage of occupancy of the hash table. % is defined as  (GetLength()/ARR_SIZE) * 100
	int GetPercetageOfOccupancy() const;

	/***********************************************************************************************/

	//pre:	object has been instantiated 
	//post:	prints the entire table to the console denoting empty spaces
	void PrintTable();

	/***********************************************************************************************/

protected:

	/***********************************************************************************************/

	//The following functions all fufil the same purpose - they each take in a DataType, perform some mathmatical
	//operations, and return an integer value from 0 through ARR_SIZE - 1 and that is also a multiple of BUCKET_SIZE. 
	//For specific implementation details of each hash function, see .cpp
	int Hash_1(/*in*/DataType data);		//data to hash

	int Hash_2(/*in*/DataType data);

	int Hash_3(/*in*/DataType data);

	int Hash_4(/*in*/DataType data);

	int Hash_5(/*in*/DataType data);

	int Hash_6(/*in*/DataType data);

	/***********************************************************************************************/


private:


	/***********************************************************************************************/
	
	ItemType table[ARRAY_SIZE]; //pdm is array, init size of 500
	
	int currPos;				//current position of the list
	int collisions;				//analysis pdm - tracks collisions
	int length;					//analysis pdm - tracks unique elements
	int duplcates;				//analysis pdm - tracks duplicate elements
	int subsColli;				//analysis pdm - tracks subsiquent collisions
};