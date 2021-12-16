/*
  book.cpp
  Author: M00521789
  Created: 16/03/2021
  Updated: 15/04/2021
*/

#include "book.h"

#include <iostream>

/*
  Empty default Book constructor
*/
Book::Book(){}

/*
  Book class constructor
  @param string title, the title of the book
  @param vector of strings, the author(s) of the book
  @param string ISBN, the ISBN of the book
  @param int quantity, the quantity of the book in the library
*/
Book::Book(std::string title, std::vector<std::string> authors,
	   std::string ISBN, int quantity){
  this->title = title;
  this->authors = authors;
  this->ISBN = ISBN;
  this->quantity = quantity;
}

/*
  Book destructor
*/
Book::~Book(){
  // free the memory used by the authors vector
  this->authors.clear();
  this->authors.shrink_to_fit();
}

/* Getters for member variables */
std::string Book::getTitle(){
  return this->title;
}

std::vector<std::string> Book::getAuthors(){
  return this->authors;
}

std::string Book::getISBN(){
  return this->ISBN;
}

int Book::getQuantity(){
  return this->quantity;
}

/* Setter for quantity member variable */
void Book::setQuantity(int quantity){
  this->quantity = quantity;
}

/*
  Overloader for ostream, formats and prints member variables
  This function is a friend, so can access private member variables
  @return ostream, the stream containing info about the book
*/
std::ostream &operator<<(std::ostream &output, Book const &book){
  output << "\n---------------------------------\n"
	 << "Title        | " << book.title << "\n"
	 << "Authors      | ";
  for (unsigned long int i = 0; i < book.authors.size(); i++){
    if (i != book.authors.size() && i != 0){
      output << ", ";
    }
    output << book.authors.at(i);
  }
    
  output << "\nISBN         | " << book.ISBN << "\n"
	 << "Quantity     | " << std::to_string(book.quantity) << "\n"
	 << "---------------------------------\n";
  return output;
}
  
