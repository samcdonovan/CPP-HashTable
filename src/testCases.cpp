#define CATCH_CONFIG_MAIN

/*
  testCases.cpp
  Author: M00521789 
  Created: 30/03/2021
  Updated: 15/04/2021
*/

#include "catch.hpp"
#include "hashTable.h"
#include "book.h"
#include "library.h"

/*
  Helper function to populate a table with dummy data
  @param ht, the hash table to be populated
  @param quantity, the amount of pairs to put into the table
*/
void populateTable(HashTable* ht, unsigned lowerBound, unsigned upperBound){
  std::string title;
  
  std::vector<std::string> authors;
  authors.push_back("Bar");
  for(unsigned i = lowerBound; i < upperBound; i++){
    
    title = std::to_string(i);
    Book* book = new Book(title, authors, "TEST", 1);
   
    (*ht)[title] = *book;
    delete book;    
  }
}

/*
  Helper function to remove an amount of pairs from the table
  @param ht, the hash table to remove pairs from
  @param quantity, the quantity of pairs that will be removed
*/
void removeFromTable(HashTable* ht, unsigned quantity){

  std::string key;
  unsigned i = 0;

  while (ht->getTotal() > quantity){
    
    if (i > ht->getSize() - 1)
      i = 0;

    if (ht->getTable()[i] != nullptr)
      ht->remove(i);
    
    i++;
  }
}

/*
  Helper function to check every position in the hash table
  @param ht, the hash table to be checked
  @return true if there are no pairs in the table, false otherwise
*/
bool checkEmptyTable(HashTable* ht){
  Pair** table = ht->getTable();
  for (unsigned i = 0; i < ht->getSize(); i++) {
    if (table[i] != nullptr)
      return false;
  }
  return true;
}

/*
  Helper function to search every for matching keys in the whole table
  @param ht, the hash table to be searched
  @return unsigned count, the number of correct searches
*/
unsigned searchKeys(HashTable* ht){
  
  unsigned count = 0;
  
  for (unsigned i = 0; i < ht->getSize(); i++){
    /* Used to test the search() function */
    if (ht->search(std::to_string(i)) != nullptr)
      count++;
    
  }
  return count;
}

/*
  Helper function to get number of pairs in table
  @param ht, the hash table to be checked
  @return unsigned count, number of pairs in the table
*/
unsigned countNumberOfPairs(HashTable* ht){
  Pair** table = ht->getTable();
  unsigned count = 0;
  for (unsigned i = 0; i < ht->getSize(); i++) {
    if (table[i] != nullptr)
      count++;
  }
  return count;
}

TEST_CASE("creating a book object", "[book]"){
  std::vector<std::string> authors;
  
  authors.push_back("Bar");
  Book* book = new Book("Test Book", authors, "9876543210982", 1);
 
  REQUIRE(book->getTitle() == "Test Book");
  REQUIRE(book->getAuthors().size() == 1);
  REQUIRE(book->getISBN() == "9876543210982");
  REQUIRE(book->getQuantity() == 1);

  delete book;
  
}

TEST_CASE("creating a hashTable object", "[hashTable]"){
  
  HashTable* ht = new HashTable(400);
  std::vector<std::string> authors;
  authors.push_back("Bar");
  Book* book = new Book("Foo", authors, "TEST", 2);

  // assert that every position is empty when the hash table is created
  REQUIRE(checkEmptyTable(ht));
  
  /* the size of the table will be the next prime after 400 * 2.5 */
  REQUIRE(ht->getSize() == ht->findNextPrime(400 * 2.5)); 
  ht->put("Foo", *book);
   
  // assert that every position is no longer empty after inserting a pair
  REQUIRE(!checkEmptyTable(ht));
  REQUIRE(ht->getSize() == ht->findNextPrime(400 * 2.5));
  REQUIRE(ht->getTotal() == 1);

  delete book;
  delete ht;
}

TEST_CASE("putting key-value pairs into table", "[put]"){
  std::vector<std::string> authors;
  authors.push_back("bar");
  HashTable* ht = new HashTable(400);
  Book* book1 = new Book("Foo", authors, "TEST", 2);
  Book* book2 = new Book("Bar", authors, "TEST", 2);
  
  SECTION("putting pairs changes the quantity"){
    REQUIRE(ht->getTotal() == 0);
    
    ht->put("Foo", *book1);
    REQUIRE(ht->getTotal() == 1);
    
    ht->put("Bar", *book2);
    REQUIRE(ht->getTotal() == 2);
    
    populateTable(ht, 0, 50);
    REQUIRE(ht->getTotal() == 52);

    removeFromTable(ht, 0);
    REQUIRE(countNumberOfPairs(ht) == 0);
    
    /* put 1 million pairs into the table.
       this will take longer than other tests due to how many resizes there will be */
    populateTable(ht, 0, 1000000);
    
    /* assert that there are now 1 million pairs in the table */
    REQUIRE(ht->getTotal() == 1000000);
    REQUIRE(countNumberOfPairs(ht) == 1000000);
    REQUIRE(searchKeys(ht) == 1000000);
    
  }
  delete book1;
  delete book2;
  delete ht;
}

TEST_CASE("removing elements from the table", "[remove]"){
  std::vector<std::string> authors;
  authors.push_back("Bar");
  HashTable* ht = new HashTable(400);
  Book* book = new Book("Foo", authors, "TEST", 1);
  unsigned position;
  SECTION("removing pairs changes the total"){
    REQUIRE(ht->getTotal() == 0);

    ht->put("Foo", *book);
    REQUIRE(ht->getTotal() == 1);
    
    ht->remove(ht->position("Foo"));
    REQUIRE(ht->getTotal() == 0);
    
    /* position returns the size of the table if key is not found */
    REQUIRE(ht->position("Foo") == ht->getSize());

  }

  SECTION("removing a pair causes a search fail"){
    ht->put("Foo", *book);
    position = ht->position("Foo");
    REQUIRE(position != ht->getSize());
    REQUIRE((*ht)[position] != nullptr);
    
    ht->remove(ht->position("Foo"));

    position = ht->position("Foo");
    REQUIRE(position == ht->getSize()); // position will return size if search fail
    REQUIRE((*ht)[position] == nullptr); // search will return a nullptr

  }
  
  SECTION("removing all pairs makes the table empty"){
    populateTable(ht, 0, 100);
    REQUIRE(ht->getTotal() == 100);

    REQUIRE(!checkEmptyTable(ht)); 
    removeFromTable(ht, 0); // remove all elements from the table
     
    REQUIRE(checkEmptyTable(ht)); // returns true if there are no pairs in table
    REQUIRE(ht->getTotal() == 0); // total should equal 0, nothing has been inserted
    REQUIRE(countNumberOfPairs(ht) == 0); // number of pairs in table reflects this
  }
  delete book;
  delete ht;
}


TEST_CASE("searching by key returns the correct value", "[search]"){
  
  std::vector<std::string> authors;
  authors.push_back("Bar");
  HashTable* ht = new HashTable(400);
  Book* book = new Book("Foo", authors, "TEST", 1);
 
  SECTION("putting a pair and then searching for that pair by key returns the correct pair"){
    ht->put("Foo", *book);
    REQUIRE(ht->search("Foo")->value.getTitle() == "Foo");
    REQUIRE(ht->search("Foo")->key == "Foo"); // key is the same as entered key
    REQUIRE(ht->position("Foo") != ht->getSize()); // position in table is valid
  }

  SECTION("searching for a pair that has not been inserted into the table fails"){
    REQUIRE(ht->search("Bar") == nullptr);
    REQUIRE(ht->position("Bar") == ht->getSize());
  }

  SECTION("populating a table and then searching for every entered key does not fail"){
    populateTable(ht, 0, 100);
    REQUIRE(searchKeys(ht) == 100);

    populateTable(ht, 101, 201);
    REQUIRE(searchKeys(ht) == 200);
  }
  delete book;
  delete ht;
}

TEST_CASE("hash table will change size when enough pairs are added or removed", "[resize]"){
  HashTable* ht = new HashTable(400);
  HashTable* ht2 = new HashTable(2000000);
  
  unsigned size = ht->getSize();
  unsigned size2 = ht2->getSize();
  unsigned quantity = size * 0.4;
  
  SECTION("adding elements until the table is at least 50% full doubles table size"){
    REQUIRE(size == ht->getSize());
    
    populateTable(ht, 0, quantity); // add until table total is at 70%
  
    REQUIRE(size == ht->getSize()); // size does not change at 70% capacity
    
    populateTable(ht, quantity, size * 0.5); // add elements until 75% capacity
   
    REQUIRE(ht->getSize() == ht->findNextPrime(size * 2)); // size should be doubled

    /* assert that the number of pairs in the table after resize is the same */
    REQUIRE(countNumberOfPairs(ht) == (unsigned)(size * 0.5));
  }
  
  SECTION("removing elements until the table is at most 12.5% full halves table size"){
    REQUIRE(size == ht->getSize());

    populateTable(ht, 0, size * 0.4); // populate until 40% capacity

    removeFromTable(ht, size * 0.2); // remove until 20% capacity

    REQUIRE(ht->getSize() == size); // size does not change

    removeFromTable(ht, size * 0.1); // remove elements so that there is < 12.5%

    REQUIRE(ht->getSize() == ht->findNextPrime(size / 2)); // size should be halved
    REQUIRE(countNumberOfPairs(ht) == (unsigned) (size * 0.1));
  }

  SECTION("testing a large resize: 2000000 to 4000000"){
    
    REQUIRE(size2 == ht2->getSize());
    std::cout << "Inserting " << (size2 / 2) << " pairs. This should not take long.\n";
    populateTable(ht2, 0, (size2 / 2) -1 ); // populate table with 1000000 pairs

    REQUIRE(ht2->getSize() != ht->findNextPrime(size2 * 2));

    populateTable(ht, (size2 / 2) - 1, (size2 / 2));
    
  }
  delete ht;
  delete ht2;
}

TEST_CASE("hash table size edge cases", "[hash table size]"){
  unsigned maxUint = std::numeric_limits<unsigned>::max();
  std::cout << "Creating a hash table with " << (maxUint / 2.5) << " pairs in it. This should not take long.\n";
  HashTable* maxHT1 = new HashTable(maxUint / 2.5);
  HashTable* minHT = new HashTable(0);
  bool minusException = false;
  
  bool sizeException = false;
  
  CHECK(maxHT1->getSize() == maxUint);
  
  SECTION("setting max int as the size throws an exception"){
    
    HashTable* exceptionHT = nullptr;
    try {
      exceptionHT = new HashTable(maxUint);
   
    } catch(const std::bad_array_new_length &e) {
      CHECK(std::string(e.what()) == "std::bad_array_new_length");
      sizeException = true;
    } catch(const std::bad_alloc &e){
      sizeException = true;
    }
    CHECK(!sizeException);
    delete exceptionHT;
  }
  
  /* size should be 2, the first prime after 0 */
  REQUIRE(minHT->getSize() == 2);


  SECTION("setting -1 as the size throws an exception"){
    HashTable* minusHT = nullptr;
       try {
     minusHT = new HashTable(-1);
   
    } catch(const std::bad_array_new_length &e) {
      CHECK(std::string(e.what()) == "std::bad_array_new_length");
      minusException = true;
    } catch(const std::bad_alloc &e){
      minusException = true;
    }
    CHECK(!minusException);
    delete minusHT;
  }
  delete maxHT1;
  delete minHT;
}
  
