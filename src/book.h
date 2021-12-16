#ifndef _BOOK_H
#define _BOOK_H

/*
  book.h
  M00521789
  Created: 16/03/2021
  Updated: 15/04/2021
*/

#include <string>
#include <vector>

/*
  Book class
  Used to store the books in the library system
  Member variables consist of information about the book
*/
class Book {
private:
  std::string title;
  std::vector<std::string> authors;
  std::string ISBN;
  int quantity;
public:
  Book();
  Book(std::string title, std::vector<std::string> authors,
       std::string ISBN, int quantity); // constructor
 
  ~Book(); // destructor

  /* getters for member variables */
  std::string getTitle();
  std::vector<std::string> getAuthors();
  std::string getISBN();
  int getQuantity();

  /* setter for quantity */
  void setQuantity(int quantity);

  /* ostream overloader used to format and print member variables */
  friend std::ostream &operator<<(std::ostream &os, const Book &book);
  
};

#endif
