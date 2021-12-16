/*
  hashTable.cpp
  Author: M00521789 
  Created: 07/04/2021
  Updated: 15/04/2021
*/

#include "hashTable.h"

#include <functional>
#include <iostream>

/* HashTable constructor */
HashTable::HashTable(unsigned inputSize){
  this->total = 0;
  this->size = initialSize(inputSize); /* initial size is calculated based on input */
  this->table = new Pair*[size];
   
  for (unsigned i = 0; i < size; i++)
    this->table[i] = nullptr;
}

/* HashTable destructor */
HashTable::~HashTable(){
  for (unsigned i =0; i < size; i++)
    delete table[i];
  delete[] table;
}

/* Getters for the private member variables */
Pair** HashTable::getTable(){
  return this->table;
}

unsigned HashTable::getSize(){
  return this->size;
}

unsigned HashTable::getTotal(){
  return this->total;
}

/*
  Hash function that takes a key and creates a hash number
  @param string key, the key to be hashed.
  @return unsigned int, the hash value of the key.
*/
unsigned HashTable::hash(std::string key){
  unsigned hashCode = 5381;
  int length = key.size(); /* key is assumed to be a string */
  while(length != 0){ /* loops for the length of the key */
    length--;
    hashCode = (hashCode * 33) + key[length]; /* adds value of current char */
  }
    
  /* then mod it by the table size */
  hashCode = hashCode % size;
  return hashCode;
}

/*
  Takes a key and finds the position of that key in the table.
  @param string key, the key to find the position for.
  @return unsigned int, its position in the table.
*/
unsigned HashTable::position(std::string key){
  unsigned hashCode = hash(key);
  unsigned index = hashCode;

  /* Probes through the table until the entered key is found,
     then returns that index. Must run at least once. */
  do {
    
    if(table[index] != nullptr
       && table[index]->key == key)
      return index;
      
    if (index == size - 1)
      index = 0;
    else
      index++;

  } while(table[index] != nullptr && index != hashCode);

  /* if key is not found, returns size, as this will be out of bounds */
  return size; 
}

/*
  Searches the hash table for the pair that corresponds to the key.
  @param K datatype, the key used to search the table.
  @return Pair, the key-value pair that matches the entered key.
*/
Pair* HashTable::search(std::string key){
  unsigned index = position(key);
 
  if (index == size)
    return nullptr;
  else
    return table[index];
}
  
/*
  Main put function, puts key-value pair into table.
  @param string key, the key of the pair.
  @param Book value, the value associated with that key.
*/
void HashTable::put(std::string key, Book value){
  unsigned hashCode = hash(key);
  Pair* nodePtr = new Pair(key,value);
 
    /* Use linear probing to find a position in the table that is empty,
       or a key that matches the key that is being inserted.
       This will only run if the hash code is in a cluster */
    while (table[hashCode] != nullptr
	   && table[hashCode]->key != key){
      if (hashCode == size - 1)
	hashCode = 0;
      else
	hashCode++;
    }
    
    if(table[hashCode] != nullptr && table[hashCode]->key == key)
      table[hashCode]->value = value;
    else {
      table[hashCode] = nodePtr; 
      total++;
    }
  
  /* if the current total is 50% of the size, double the size */
  if (total >= size / 2)
    resize(size * 2);
  
  // delete &nodePtr;
  nodePtr = nullptr; 
}

/*
  Main delete function; removes key-value pair from table.
  @param unsigned int index, the index of the pair to be removed.
*/
void HashTable::remove(unsigned index){
    
  std::string tempKey;
  Book tempValue;
    
  if (index == size) /* break out of function if index is out of bounds */
    return;
    
  delete table[index];
  table[index] = nullptr;
  total--;

  /* Add 1 to the index to get to the next position in the table */
  if (index == size - 1)
    index = 0;
  else
    index++;

  /* Linear probe until empty position is found. 
     Delete and re-put every pair in the cluster back into the table. */
  while(table[index] != nullptr) {
    tempKey  = table[index]->key;
    tempValue = table[index]->value;
     
    table[index] = nullptr;

    put(tempKey, tempValue);
    total--;
      
    if (index == size - 1)
      index = 0;
    else
      index++;
  }
  /* if current total is 12.5% of size, half the size */
  if (total <= size * 0.125 && total > 0)
    resize(size/2);
}

/*
  Resizes the table based on the current total.
  @param int newsize, the size to change to.
*/
void HashTable::resize(unsigned size){
  Pair** tempArray = table;
  std::string tempKey = "";
  Book tempValue;
  unsigned oldSize = this->size;

  /* Find the next prime after the input size */
  size = findNextPrime(size);
    
  table = new Pair*[size];
  
  for (unsigned i = 0; i < size; i++)
    table[i] = nullptr;

  /* set this->size to the next prime after the input size */
  this->size = size;
    
  for (unsigned i = 0; i < oldSize; i++){
    if(tempArray[i] != nullptr){
	
      tempKey = tempArray[i]->key;
      tempValue = tempArray[i]->value;

      tempArray[i] = nullptr;

      put(tempKey, tempValue);
      total--;
    }
  }
  delete *tempArray;
}

/*
  [] overloader; used when putting a book into the table 
  @param string key, the key of the book to be inserted
  @return Book&, a reference to the book that was inserted
*/
Book& HashTable::operator[](std::string key){
  unsigned index = position(key);
  if (index == size) // if key does not exist, insert book
    put(key, Book());
  
  index = position(key);
  return table[index]->value;
}

/*
  [] overloader; used when removing and searching for a book
  @param unsigned int, index of the book
  @return Book*, a pointer to the book in the table
*/
Book* HashTable::operator[](unsigned index){
  if (index == size || table[index] == nullptr)
    return nullptr;
  Book* book = &table[index]->value;
  return book;
}

/*
  Helper function to set the initial size
  @param unsigned int inputSize, the size of the input
  @return unsigned int, the next prime after the input multiplied by 2.5
*/
unsigned HashTable::initialSize(unsigned inputSize){
  return findNextPrime(inputSize * 2.5);
}

/*
  Helper function to check if an number is a prime
  @param unsigned int n, the number to check
  @return bool, returns true if the number is a prime
*/
bool HashTable::isPrime(unsigned n){
  
  if (n == 0 || n == 1)
    return false;

  for (unsigned i = 2; i <= n/2; i++){
    if (n % i == 0)
      return false;
  }
  return true;
}

/*
  Helper function to find the next prime after a number
  @param unsigned int n, the number to start from
  @return unsigned int, the next prime
*/
unsigned HashTable::findNextPrime(unsigned n){

  while(!isPrime(n)){
    n++;
  }
  return n;
}
