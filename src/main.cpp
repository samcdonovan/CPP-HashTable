/*
  main.cpp
  Author: M00521789 
  Created: 15/03/2021
  Updated: 15/04/2021
*/

#include "library.h"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){
  if (argc != 2){
    std::cerr << "Usage: " << argv[0]
	      << " <file-name>\n";
    exit(1);
  }

  std::ifstream file(argv[1]); // takes file from command line arg
  if(!file.is_open()){
    std::cerr << "Error: " << argv[1]
	      << " not found.\n";
    exit(1);
  }
  
  Library* library = new Library(argv[1]); // passes the filepath to library constructor
 
  
  std::string userInput;
  bool quit = false;
  
  while(!quit){ // main loop of the program
      
    std::cout << "\n---------------------------------------------\n"
	      << "\nHello User! Welcome to the book search system!\n\n"
	      << "Search for a book (by title)........1\n"
	      << "Add a book..........................2\n"
	      << "Remove a book.......................3\n"
	      << "Quit................................0\n"
	      << "\n---------------------------------------------\n"
	      << "Please select an option from the menu (1, 2, 3 or 0) > ";
 
    std::cin >> userInput;
    std::cin.clear();
    std::cin.ignore(256, '\n');

    // calls a library function depending on users input
    if (userInput == "1")
      library->search();
    else if(userInput == "2")
      library->add();
    else if(userInput == "3")
      library->reduceQuantity();
    else if(userInput == "0"){
      std::cout << "\nYou have chosen to quit. Goodbye!\n";
      quit = true;
    } else {
      std::cout << "\n---------------------------------------------\n"
		<< userInput << " is not an option in the menu.\n"
		<< "Please enter 1, 2, 3 or 0 for the corresponding choice.\n"
		<< "\n---------------------------------------------\n";
    }
  }
  delete library;
  return 0;
}
