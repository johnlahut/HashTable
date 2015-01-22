/*
Author: John Lahut
Date: 12/22/2014
Project: HashTable
Filename: Source.cpp
Purpose: Provides the I/O for a a given ADT hash table
*/


#include "HashTable.h"
#include<iostream>	//file i/o
#include<fstream>	//file vars
#include<cctype>	//for toupper

using namespace std;

//Named constants

const int UPPER_ASCII_LIMIT = 91;
const int LOWER_ASCII_LIMIT = 64;
const int UNDERSCORE_ASCII = 95;

const string OUTPUT_FILE = "stats.out";
const string INPUT_FILE = "hashing.txt";
const string BEGIN_TEST_FILE = "-----TEST SUMMARY-----";
const string CRP_DESCRIP = "Hash table using a CRP of Bucketing. Bucket size currently set to ";
const string INIT_COLLISIONS = "Number of initial collisions encountered: ";
const string NUM_ITEMS_INSERTED = "Number of items inserted: ";
const string DUPLICATE_KEYS = "Number of duplicate keys: ";
const string SUBSIQ_COLLISIONS = "Number of subsiquent collisions: ";
const string TOTAL_COLLISIONS = "Total number of collisions: ";
const string TABLE_SIZE = "Size of table: ";
const string PERCENT_OCCU = "Percentage of occupancy: ";
const string PERCENT = "%";
const string TOTAL_WORDS_READ = "Total number of words read in: ";
const string END_TEST_FILE = "---------------------";
const string OCCURS = " occurs ";
const string TIMES = " times.";


void main()
{

	HashTable myhash;
	fstream indat;
	ofstream outdat(OUTPUT_FILE);
	ItemType item;


	/*           READING HASHING.TXT IN            */

	char letter;
	string line;


	//Reads each character in one at a time, verifying that it is a valid word. Once the end of a word is reached,
	//it is passed to Insert to put it into the ADT HashTable

	indat.open(INPUT_FILE);

	indat.get(letter);
	letter = toupper(letter);

	line = letter;

	while (indat)
	{
		indat.get(letter);

		letter = toupper(letter);

		if ((letter > LOWER_ASCII_LIMIT && letter < UPPER_ASCII_LIMIT) || letter == UNDERSCORE_ASCII)
		{
			line += letter;
		}
		else
		{
			if (line != EMPTY_DATA)
			{
				item.data = line;
				item.count = 0;
				myhash.Insert(item);
				line = EMPTY_DATA;
			}
		}
	}

	indat.close();
	
	/*           END FILE READ        */

	//myhash.PrintTable();

	/*       BEGIN OUTPUT FILE        */

	outdat << BEGIN_TEST_FILE << endl << endl;

	outdat << CRP_DESCRIP << BUCKET_SIZE << endl;
	outdat << INIT_COLLISIONS << myhash.GetNumCollisions() << endl;
	outdat << NUM_ITEMS_INSERTED << myhash.GetLength() << endl;
	outdat << DUPLICATE_KEYS << myhash.GetDuplicates() << endl;
	outdat << SUBSIQ_COLLISIONS << myhash.GetSubsCollisions() << endl;
	outdat << TOTAL_COLLISIONS << myhash.GetSubsCollisions() + myhash.GetNumCollisions() << endl;
	outdat << TABLE_SIZE << ARRAY_SIZE << endl;
	outdat << PERCENT_OCCU << myhash.GetPercetageOfOccupancy() << PERCENT << endl;
	outdat << TOTAL_WORDS_READ << myhash.GetLength() + myhash.GetDuplicates() << endl;
	outdat << END_TEST_FILE << endl << endl;

	myhash.FirstPosition();
	while (!myhash.EndOfList())
	{
		item = myhash.Retrieve();
		if (item.data != EMPTY_DATA)
			outdat << item.data << OCCURS << item.count << TIMES << endl;
		myhash.NextPosition();
	}

	outdat.close();
	
	/*     END OUTPUT FILE     */

}//end main