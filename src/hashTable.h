#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

/*
  hashTable.h
  Author: M00521789 
  Created: 07/04/2021
  Updated: 15/04/2021
*/

#include "book.h"

/*
  Pair struct; used to store key-value pairs
  A key-value struct was used instead of two arrays to keep the code 
  slightly more simple/readable.
*/
struct Pair {
  /* keys and values are template types */
  std::string key;
  Book value;
  
  /* Constructor sets key and value */
  Pair(std::string key, Book value){
    this->key = key;
    this->value = value;
  }
};

/*
  Main Hash Table class
  This is the data structure used to store the Books.
  The collision resolution method is Linear Probing.
*/
class HashTable {
private:
  /* associative array created using the Pair struct */
  Pair** table; 

  unsigned size; /* size of the table (will always be an unsigned prime) */
  unsigned total; /* total number of pairs in the table */

public:

  /* HashTable constructor */
  HashTable(unsigned inputSize);

  /* HashTable destructor */
  ~HashTable();

  /* Getters for the private member variables */
  Pair** getTable();
  unsigned getSize();
  unsigned getTotal();

  /* Main hash table functions */
  unsigned hash(std::string key);
  
  unsigned position(std::string key);
  
  Pair* search(std::string key);
  
  void put(std::string key, Book value);
  
  void remove(unsigned index);

  void resize(unsigned size);
 
  /* Helper functions for the size of the table */
  unsigned initialSize(unsigned inputSize);
  bool isPrime(unsigned n);
  unsigned findNextPrime(unsigned n);

  /* [] overloaders to perform main functions */
  Book& operator[](std::string key);
  Book* operator[](unsigned index);
};

#endif
