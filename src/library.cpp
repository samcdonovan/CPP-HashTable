/*
  library.cpp
  Author: M00521789 
  Created: 29/03/2021
  Updated: 15/04/2021
*/

#include "library.h"

#include <limits>
#include <fstream>
#include <iostream>

/*
  Library class constructor
  @param string, the file to load data from
*/
Library::Library(std::string file){
  /* load the data into the hash table */
  this->ht = loadData(file);
}

/* Library destructor */
Library::~Library(){
  delete this->ht;
}

/*
  Helper function to calculate the number of lines in a file
  @param string file, the file to calculate the number of lines from
  @return unsigned int, the number of lines
*/
unsigned numberOfLines(std::string file){
  
  unsigned numberOfLines = 0;
  std::string line;
  std::ifstream myfile(file);

  while (std::getline(myfile, line))
    ++numberOfLines;
    
  return numberOfLines;
}

/*
  Loads data into the hash table from a file.
  @param string, the file to load data from.
  @return hash table, the hash table with data loaded into it.
*/
HashTable* Library::loadData(std::string file){
  HashTable* ht = new HashTable(numberOfLines(file));
  
  std::string line, title, authorsLine, ISBN;
  int quantity;
  std::vector<std::string> authors;

  std::ifstream bookFile(file);

  if (bookFile.is_open()){

    while(getline(bookFile, line)){

      /* each member variable is separated by a tab in the file */
      title = line.substr(0, line.find('\t'));
      line.erase(0, line.find('\t') + 1);

      authorsLine = line.substr(0, line.find('\t'));
      while (authorsLine != ""){
	/* separate the authors by the ';' char */
	if (authorsLine.find(';') == std::string::npos){ // if there are no more ';' chars
	  authors.push_back(authorsLine.substr(0, authorsLine.find('\t')));
	  authorsLine = "";
	} else {
	  authors.push_back(authorsLine.substr(0, authorsLine.find(';')));
	  /* if there are still ';' chars in the line, 
	     push each author to the authors vector */
	  authorsLine.erase(0, authorsLine.find(';') + 2);
	}
      }

      line.erase(0, line.find('\t') + 1);
      
      ISBN = line.substr(0, line.find('\t')); 
      line.erase(0, line.find('\t') + 1);
	
      quantity = atoi(line.substr(0, line.find('\t')).c_str());

      /* create a new Book object with the member variables from the file. */
      Book* book = new Book(title, authors, ISBN, quantity);
      (*ht)[title] = *book; /* put the book into the table */
      authors.clear();
      delete book;
    }
  }
  return ht;
}

/*
  Prompts the user to enter a title and displays the book if found,
  or displays a message notifying the user that it was not found.
*/
void Library::search(){
  std::string title;
  
  std::cout << "\nYou have chosen to search for a book.\n"
	    << "\nPlease enter the title of the book (case-sensitive) > ";
  std::getline(std::cin, title);

  Pair* book = ht->search(title);
 
  if (book != nullptr){
    std::cout << book->value; // use << overloader from book class
  } else {
    std::cout << "\n---------------------------------------------\n"
	      << "\nNo books called '" << title << "' exist within the system.\n"
	      << "\n---------------------------------------------\n";  
  }
}

/*
  Main add function, allows user to either 
  increase stock or add a new book.
*/
void Library::add(){
  bool quit = false;
  std::string userInput;
  
  while(!quit){
    std::cout<<"\n---------------------------------------------\n"
	     << "\nWould you like to increase the quantity of a book that is currently in the"
	     << " system, or add a new book?\n\n"
	     << "Increase quantity for a book........1" << "\n"
	     << "Add a new book......................2" << "\n"
	     << "Back to main menu...................0" << "\n"
	     <<"\n---------------------------------------------\n"
	     << "Please enter your choice (1, 2 or 0) > ";
    
    std::cin >> userInput;
    std::cin.clear();
    std::cin.ignore(256, '\n');
    
    if (userInput == "1"){
      increaseQuantity();
    } else if (userInput == "2"){
      addNewBook();
    } else if (userInput == "0"){
      quit = true;
    } else {
      std::cout << "\n---------------------------------------------\n"
		<< "\nPlease choose either 1 (to increase the stock of a book), "
		<< "2 (to add a new book) or 0 to go back to the main menu.\n"
		<< "\n---------------------------------------------\n";
    }
  }
}

/*
  Helper function for add functionality.
  Increases the stock of the book that the user enters.
*/
void Library::increaseQuantity(){
  int quantity;
  std::string title;
  std::cout << "\nPlease enter the title of the book (case-sensitive) > ";
  std::getline(std::cin, title);
  
  Pair* book = ht->search(title);
  
  if (book != nullptr){
    quantity = book->value.getQuantity();
    std::cout << "\n---------------------------------------------\n"
	      << "Increasing the quantity of '" + title + "'.\n"
	      << "\nUpdated quantity from " << quantity << " to "
	      << quantity + 1 << ".\n";
     
    book->value.setQuantity(quantity + 1);
         
  } else {
    std::cout << "\n---------------------------------------------\n"
	      << "\nNo books called '" << title << "' exist within the system.\n"
	      << "\n---------------------------------------------\n";  
  }
}

/*
  Helper function that allows the user to add a new book to the stystem.
*/
void Library::addNewBook(){
  std::string title, author, ISBN;
  std::vector<std::string> authors;
  int quantity;
  std::string input;

  std::cout << "\nPlease enter the title of the new book (case-sensitive) > ";
  std::cin >> title;
  std::cin.clear();
  std::cin.ignore(256, '\n');
  
  std::cout << "\nPlease enter an authors name > ";
  std::cin >> author;
  authors.push_back(author);

  while (input != "2"){ // loop to add more than one author
    std::cout <<"\n---------------------\n"
	      << "\nAdd another author?\n"
	      << "Yes...............1\n"
	      << "No................2\n"
	      <<"\n---------------------\n"
	      << "Please enter your choice > ";
    
    std::cin >> input;

    if (input == "1"){

      std::cout << "\nPlease enter an authors name > ";
      std::cin >> author;
      authors.push_back(author);

    } else if (input != "2"){

      std::cout << "\nPlease choose either 1 for yes or 2 for no.\n";
      std::cin.clear();
      std::cin.ignore();
    }
  }
  
  ISBN = validISBN();
  
  std::cout << "\nPlease enter the quantity for this book > ";
  quantity = validQuantity();
   
  Book* book =  new Book(title, authors, ISBN, quantity);
  
  std::cout << "\nThe following book has been added to the system:\n";
  std::cout << *book;
  
  (*ht)[title] = *book; // use [] overloader to insert the book
  delete book;
}

/*
  Prompts the user to enter a title, and then calls the remove
  function on that title.
*/
void Library::reduceQuantity(){
  
  std::string title;
  int quantity;
  std::cout << "\nYou have chosen to reduce the quantity of a "
	    << "book in the library.\nIf that book has only 1 remaining "
	    << "copy, it will be removed from the system.\n"
	    << "\nPlease enter the name of the book (case-sensitive) > ";
  std::getline(std::cin, title);
  
  unsigned index = ht->position(title);
  Book* book;

  if (index == ht->getSize()){
    std::cout << "\n---------------------------------------------\n"
	      << "\nNo books called '" << title << "' exist within the system.\n"
	      << "\n---------------------------------------------\n";
    return;
  }
  
  book = (*ht)[index];
  quantity = book->getQuantity();

  if (quantity == 1){
     
    std::cout << "\n---------------------------------------------\n"
	      << "\nThere is only 1 copy of '" + title + "' left in the system.\n\n";
   
    ht->remove(index);
      
    std::cout <<"'"+ title + "' has been removed from the system.\n"
	      << "\n---------------------------------------------\n";
  } else {
    std::cout << "\n---------------------------------------------\n"
	      << "\nRemoving one copy of '" << title << "'\n"
	      << "\nUpdated quantity from " << quantity << " to "
	      << quantity - 1 << ".\n";
    quantity--;
    book->setQuantity(quantity);
	
  }
}

/*
  Helper function that prompts the user until they enter a positive integer.
  @return int, a valid positive integer.
*/
int Library::validQuantity(){
  int x;
  std::cin >> x;
  while(std::cin.fail() || x < 0 || x > std::numeric_limits<int>::max()){
 
    std::cout << "\nPlease enter a positive integer > ";
    
    std::cin.clear();
    std::cin.ignore();
    
    std::cin >> x;
  }
  return x;
}

/*
  Helper function that prompts the user until they enter a valid ISBN.
  @return string, a valid ISBN.
*/
std::string Library::validISBN(){
  std::string input;
  
  /* input is valid if it is 13 characters long */
  while(input.size() != 13 || input.substr(0, 3) != "978"){ 
    std::cout << "\nPlease enter the unique ISBN for this book "
	      << "(this must be a number with 13 digits in it, starting with 978, e.g.9780521780988)  > ";
    std::cin.clear();
    std::cin.ignore();
    
    std::cin >> input;
  }
  return input;
}

