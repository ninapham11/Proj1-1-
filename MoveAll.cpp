#include "MoveAll.hpp"
#include "Book.hpp"
/*
CSCI335 Spring 2024
Assignment 1 – Move Semantics 
Program reads Book objects, stores them in a vector of Books, 
and allows you to move Books from to another vector of Books
Name: Nina Pham
Date: 02/22/2024
*/

// Moves all Books in "source" with the specified keyword to "dest".
// A Book is moved if any of its keywords match the one specified in this function.
// Use iterators whenever appropriate.
// Hint: you need a const iterator for a const vector, but this will be automatically handled using "auto".

void moveAll (const std::string keyword, std::vector<Book> &source, std::vector<Book> &dest)

{
  const auto t1_start = std::chrono::steady_clock::now();
  int books_moved=0; // counts books moved

 //Use a for loop to traverse the source vector.
 //Declares an iterator named it of type auto pointing to the beginning of the source vector.
  for (auto it = source.begin(); it != source.end();) 
  { 
    //check if the keyword exists within the current Book
    if (std::find(it->getKeywords().begin(), it->getKeywords().end(), keyword) != it->getKeywords().end()) {
      dest.push_back(std::move(*it)); //if the keyword is found, moves the current Book object to the dest
      it = source.erase(it); // Erase the moved object from source (and get the next iterator)
      ++books_moved; //increments counter 
    } else 
    {
      ++it; // Move to the next element in source
    }
  }
  const auto t1_end = std::chrono::steady_clock::now();
  int t1 = std::chrono::duration <double, std::micro> (t1_end - t1_start).count();
  std::cout << "Moved " << books_moved << " books in " << t1 << " microseconds." << std::endl;
}
