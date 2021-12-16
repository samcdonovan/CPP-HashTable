#ifndef _LIBRARY_H
#define _LIBRARY_H

/*
  library.h
  Author: M00521789 
  Created: 29/03/2021
  Updated: 15/04/2021
*/

#include "hashTable.h"
#include "book.h"

/*
  Main library system class
  Member variable: the hash table which stores the books
  Contains functions that perform the required functionality
*/
class Library {
private:
  /* Hash table which stores the books */
  HashTable* ht; 
public:
  Library(std::string file); /* library constructor */

  ~Library();
  
  /* Loads data from a file into the table */
  HashTable* loadData(std::string file);
  
  /* Functions to perform the required library management functionality */
  void search();
  void add();
  void increaseQuantity();
  void addNewBook();
  void reduceQuantity();
  
  /* Helper functions to validate user input */
  int validQuantity();
  std::string validISBN();
   
};

#endif
