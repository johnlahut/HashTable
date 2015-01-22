/*
Author: John Lahut
Date: 12/22/2014
Project: HashTable
Filename: HashTable.cpp
Purpose: Provides the implementation for an array based ADT HashTable. This hash table is mainly used for experimentation
			analysis of a number of hash functions. Each hash function is slightly different, and then its results are
			studied. The hash function takes in a DataType and returns an int value representing the corresponding index
			in the hash table. 
Assumptions: Client is inserting and that is pretty much it. Did not provide implementation for Delete or Find (although
				Find would not be verty difficult to implement). Class currently is mainly used for analysis. File that 
				is being read in must end with a new line. (cursor is on the next line after the last line of text)
Input:		Currently input is handled in main() in the client. Reads in a .txt file defined in the client (currently set
			to "hashing.txt"
Processing: The client does not know that they are using a HashTable (well, I named the class HashTable, but other than
			that...) so it will use the list like any other ADT. Since the list is 'unordered' the client does not need to
			call find, just needs to call Insert. Duplicate keys are not inserted, however they are counted in a separate
			field.
Output:		All results and analysis are handled by client. See main() for specific details. 
*/



#include "HashTable.h"	//hash table spec
#include <iostream>
using namespace std;

/***********************************************************************************************/

//pre:	none		
//post: a new HashTable object has been created and all PDM's have been instantiated
HashTable::HashTable()
{
	//initalize PDMS
	currPos = 0;
	collisions = 0;
	length = 0;
	duplcates = 0;
	subsColli = 0;

	//Get rid of garbage values
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		table[i].count = 0;

	}//end for

}//end DC

/***********************************************************************************************/

//pre:	object has been instantiated
//post:	returns true to the caller if currPos is at the end of the list, false otherwise
bool HashTable::EndOfList() const
{
	return(currPos == ARRAY_SIZE);

}//end EndOfList

/***********************************************************************************************/

//pre:	object has been instantiated 
//post:	sets the current position of the list to the first element
void HashTable::FirstPosition()
{
	currPos = 0;

}//end FirstPosition

/***********************************************************************************************/

//pre:	object has been instantiated, not at the end of the list
//post:	sets the current position of the list to the next position in the list
void HashTable::NextPosition()
{
	if (!EndOfList())
		currPos++;
	
}//end NextPosition

/***********************************************************************************************/

//pre:	object has been instantiated
//post:	returns the element denoted by currPos to the caller
ItemType HashTable::Retrieve() const
{

	return table[currPos];

}//end Retrieve


/***********************************************************************************************/

//pre:	object has been instantiated
//		item is a valid ItemType with initalized values
//post: item has been inserted into the current object
void HashTable::Insert(/*in*/ItemType item)	//valid item to insert
{
	currPos = Hash_5(item.data);	//<---- ****** CHANGE NUMBER (1-6) after the underscore to test different hash functions ******

	//Unique key
	if (table[currPos].data == EMPTY_DATA)
	{
		table[currPos] = item;
		table[currPos].count++;
		length++;

	}//end if

	//Duplicate
	else if (table[currPos].data == item.data)
	{
		duplcates++;
		table[currPos].count++;

	}//end else if

	//Collision -- not an empty space, and not a duplicate
	else
	{
		collisions++;

		// i = currPos + 1 because we have already verified that the current currPos index cannot insert an item.
		//looping though until we find an open space (in the bucket or beyond) -- can lead to infinite probing
		//high occupancy hash tables with bucketing as CRP turns into linear probing quicker than one may think

		for (int i = currPos+1; i < ARRAY_SIZE; i++)
		{
			//reset counter if at end of list
			if (i == ARRAY_SIZE - 1)
				i = 0;

			//Need to re-check for duplicates, there may be a duplicate key in the HK's bucket. 
			if (table[i].data == item.data)			
			{
				table[i].count++;
				duplcates++;
				collisions--;
				return;

			}//end if

			else 
			{
				if (table[i].data == EMPTY_DATA)			//if the current index is an open space
				{
					table[i].data = item.data;
					table[i].count++;
					length++;
					return;

				}//end if

				else
				{
					subsColli++;				//Not an open space, its a subsiquent collision

				}//end else

			}//end else

		}//end for

	}//end else

}//end Insert

/***********************************************************************************************/

//pre:	object has been instantiated
//post:	returns the number of initial collisions the hash table has encountered
//		an initial collision occurs when a unique key is being inserted to the table that hashes to the same
//		value as a pre-existing unique key
int HashTable::GetNumCollisions() const
{
	return collisions;

}//end GetNumCollisions

/***********************************************************************************************/

//pre:	object has been instantiated
//post:	return the number of unique elements inserted into the hash table (number of elements in the table)
int HashTable::GetLength() const
{
	return length;

}//end GetLength

/***********************************************************************************************/

//pre:	object has been instantiated
//post:	returns the number of duplicate elements encountered
int HashTable::GetDuplicates() const
{
	return duplcates;

}//end GetDuplicates

/***********************************************************************************************/

//pre:	object has been instantiated
//post:	returns the number of subsequent collisions the hash table has encountered
//		a subsequent collision occurs when the CRP is in effect, and during this time the element that is 
//		being inserted encounters a collision. In this specific case, if the first bucket spot is not open, that is
//		a subsequent collision
int HashTable::GetSubsCollisions() const
{
	return subsColli;

}//end GetSubsCollisions

/***********************************************************************************************/

//pre:	object has been instantiated
//post:	returns the percentage of occupancy of the hash table. % is defined as  (GetLength()/ARR_SIZE) * 100
int HashTable::GetPercetageOfOccupancy() const
{
	float fNumElements = (float)length;
	float totalNum = (float)ARRAY_SIZE;

	return (int)((fNumElements / totalNum)*100.0);

}//end GetPercentageOfOccupancy

/***********************************************************************************************/

//pre:	object has been instantiated 
//post:	prints the entire table to the console denoting empty spaces
void HashTable::PrintTable()
{
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (table[i].data != EMPTY_DATA)
			cout << table[i].data << DOUBLE_TAB << table[i].count << endl;
		else
			cout << EMPTY_PRINT << endl;

	}//end for

}//end PrintTable

/***********************************************************************************************/

/*  Hash functions. All take in a DataType and return an index 0 - ARR_SIZE-1, and also a multiple of BUCKET_SIZE    */


//Research on XOR and bit shifting really helped. 

//All hash functions make sure the value is positive before returning. Also muluitplies by BUCKET_SIZE (to return a 
//mulitple of BUCKET_SIZE) and also uses modulo to return a value between 0 - ARR_SIZE

//Results are very interesting. Each iteration does not necissarly improve. Some have a better (lower) collision rate when
//the occupancy is high, and some have a better collision rate when the occupancy is lower. The .docx file inlcuded shows 
//these results more clearly.

/***********************************************************************************************/

//First attempt. Takes one byte at a time (char by char) and either adds or subtracts it from the keyvalue. If it 
//subtracts, it also performs a bit shift to the right by 3. Ex) if we had (int)8 << 3, 8 becomes 1. Because
// 8 = 1000 ... shift 3 bits to the right = 0001 or 1. Using bit shifts help create a seemingly random value. 
int HashTable::Hash_1(/*in*/DataType data) //valid DataType to create HashKey
{
	int wordLen = data.length();
	int keyVal = 0;

	for (int i = 0; i < wordLen; i++)
	{

		if (keyVal % 2 == 0)			//if value is even, add it to key value
			keyVal += data[i];
		
		else
		{
			keyVal -= data[i];			//value is odd subract and bit shift to the right by 3
			keyVal = keyVal << 3;

		}//end else

	}//end for
	
	if (keyVal < 0)					//make it positive
		keyVal = keyVal*-1;


	return keyVal % MAX_ELEMENTS * BUCKET_SIZE;

}//end Hash

/***********************************************************************************************/

//Attempt number two. First attempt had suprisingly good results. Instead of bit shifting, I only XOR the current keyValue
//with the current byte of the string (single char). In theory, this should create a good result because XORing char's one
//at a time should create a realtively even result set. 
int HashTable::Hash_2(/*in*/DataType data) //valid DataType to create HashKey
{
	int wordLen = data.length();
	int keyVal = 0;

	for (int i = 0; i < wordLen; i++)
	{
		keyVal = (keyVal ^ data[i]);

	}//end for

	return keyVal % MAX_ELEMENTS * BUCKET_SIZE;

}//end Hash

/***********************************************************************************************/

//Third attempt. Trying to get a little more random by bit shifting each keyValue by some arbitrary number (it seems like
//some numbers work better than others) and then XORing with the current byte. 
int HashTable::Hash_3(/*in*/DataType data) //valid DataType to create HashKey
{
	int wordLen = data.length();
	int keyVal = 0;

	for (int i = 0; i < wordLen; i++)
	{
		keyVal = (keyVal >> 33) ^ data[i];

	}//end for

	if (keyVal < 0)					//make it positive
		keyVal = keyVal*-1;

	return keyVal = keyVal % MAX_ELEMENTS * BUCKET_SIZE;

}//end Hash

/***********************************************************************************************/

//Fourth attempt. Getting a little crazy. First I bit shift to the left and right by two numbers and multiply that value.
//then I XOR it with the current byte of data. Then that result is XORed with the current key value...
int HashTable::Hash_4(/*in*/DataType data) //valid DataType to create HashKey
{
	int wordLen = data.length();
	int keyVal = 0;

	for (int i = 0; i < wordLen; i++)
	{
		//Changing 3 to 15 changes the amount of collisions SIGNIFICANTLY
		keyVal = keyVal ^ ((keyVal >> 3) * (keyVal << 5) ^ data[i]); 

	}//end for

	if (keyVal < 0)					//make it positive
		keyVal = keyVal*-1;

	return keyVal % MAX_ELEMENTS * BUCKET_SIZE;

}//end Hash

//Similar to attempt number 4, except I add instead of multiply. I think I might have been losing some data because I was
//muliplying really large numbers at times. This method actually gave very good initial results. 
int HashTable::Hash_5(/*in*/DataType data) //valid DataType to create HashKey
{
	int wordLen = data.length();
	int keyVal = 0;

	for (int i = 0; i < wordLen; i++)
	{
		keyVal = keyVal ^ ((keyVal >> 5) + (keyVal << 3) ^ data[i]);

	}//end for

	if (keyVal < 0)					//make it positive
		keyVal = keyVal*-1;

	return keyVal % MAX_ELEMENTS * BUCKET_SIZE;

}//end Hash

/***********************************************************************************************/

//Last attempt. Pretty much tried to mash everything together. Uses almost all previous hash functions traits. 
int HashTable::Hash_6(/*in*/DataType data) //valid DataType to create HashKey
{
	int wordLen = data.length();
	int keyVal = 0;

	for (int i = 0; i < wordLen; i++)
	{

		if (keyVal % 2 == 0)			//if value is even, add it to key value
		{
			keyVal = keyVal ^ ((keyVal >> 13) + (keyVal << 3) ^ data[i]);

		}//end if

		else
		{
			keyVal = keyVal ^ ((keyVal >> 3) - (keyVal << 13) ^ data[i]);

		}//end else

	}//end for

	if (keyVal < 0)					//make it positive
		keyVal = keyVal*-1;

	return keyVal % MAX_ELEMENTS * BUCKET_SIZE;

}//end hash

/***********************************************************************************************/

