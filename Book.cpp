#include "Book.hpp"
#include <memory>  // For std::unique_ptr
#include <utility> // For std::invalid_argument
/*
CSCI335 Spring 2024
Assignment 1 – Move Semantics 
Program reads Book objects, stores them in a vector of Books, 
and allows you to move Books from to another vector of Books
Name: Nina Pham
Date: 02/22/2024
*/

    // write and document all methods in this file.

    /** @post: default constructor */
    Book::Book()
    {
        // Default values for member variables:
        title_ = "";
        author_ = "";
        ISBN_ = 0;
        icon_ = nullptr; // Point to nowhere (no allocated memory)
        price_ = 0.00;
        keywords_.clear(); // Empty vector
        blurb_ = "";
    }

    /** @post : Destroy the Book object */
    Book::~Book()
    {
    // Deallocate dynamically allocated memory if necessary
        if (icon_ != nullptr) 
        {
            delete[] icon_; 
            icon_ = nullptr;
        }

        keywords_.clear();

    }


    Book::Book(const Book& rhs)
    {
        {
            // Copy member variables that can be copied directly:
            title_ = rhs.title_;
            author_ = rhs.author_;
            ISBN_ = rhs.ISBN_;
            price_ = rhs.price_;
            blurb_ = rhs.blurb_;
            keywords_ = rhs.keywords_; // Copy the vector of keywords

            // Handle dynamic memory allocation for `icon_`:
            if (rhs.icon_ != nullptr) {
                icon_ = new int[80]; // Allocate new memory for icon_
                std::copy(rhs.icon_, rhs.icon_ + 80, icon_); // Copy icon data
            } else 
            {
                icon_ = nullptr; // Set to nullptr if rhs.icon_ is nullptr
            }

        }

    }

    Book& Book::operator=(const Book& rhs)
    {

        // Handle self-assignment (assigning the object to itself)
        if (this == &rhs) {
            return *this; // Return current object without modification
        }

        // Deallocate existing memory for `icon_` (if necessary)
        delete[] icon_;
        icon_ = nullptr;

        // Copy member variables that can be copied directly:
        title_ = rhs.title_;
        author_ = rhs.author_;
        ISBN_ = rhs.ISBN_;
        price_ = rhs.price_;
        blurb_ = rhs.blurb_;
        keywords_ = rhs.keywords_; // Copy the vector of keywords

        // Handle dynamic memory allocation for `icon_`:
        if (rhs.icon_ != nullptr) 
        {
            icon_ = new int[80]; // Allocate new memory for icon_
            std::copy(rhs.icon_, rhs.icon_ + 80, icon_); // Copy icon data
        }

        return *this; // Return the modified object

    }

    Book::Book(Book&& rhs)
    {
        // Move member variables:
        title_ = std::move(rhs.title_);
        author_ = std::move(rhs.author_);
        ISBN_ = rhs.ISBN_;
        price_ = rhs.price_;
        blurb_ = std::move(rhs.blurb_);
        keywords_ = std::move(rhs.keywords_); // Move the vector of keywords

        // Move `icon_` (assuming it's an array of integers):
        icon_ = rhs.icon_;
        rhs.icon_ = nullptr; // Set rhs.icon_ to null to avoid dangling pointer

    }

    Book& Book::operator=(Book&& rhs)
    {
        // Handle self-assignment (assigning the object to itself)
        if (this == &rhs) 
        {
            return *this; // Return current object without modification
        }

        // Deallocate existing memory for `icon_` (if necessary)
        delete[] icon_;
        icon_ = nullptr;

        // Move member variables that support move semantics:
        title_ = std::move(rhs.title_);
        author_ = std::move(rhs.author_);
        ISBN_ = rhs.ISBN_;
        price_ = rhs.price_;
        blurb_ = std::move(rhs.blurb_);
        keywords_ = std::move(rhs.keywords_); // Move the vector of keywords

        // Move `icon_` (assuming it's an array of integers):
        icon_ = rhs.icon_;
        rhs.icon_ = nullptr; // Set rhs.icon_ to null to avoid dangling pointer

        return *this; // Return the modified object

    }

    /**
        @return : the name of title
    */
    const std::string& Book::getTitle() const
    {
        return title_;

    }

    /**
   @param  : the title of the Book
   @post   : sets the Book's title to the value of the parameter
    */
    void Book::setTitle(const std::string& title)
    {
        title_=title;
    }

    /**
        @return : the name of the author
    */
    const std::string& Book::getAuthor() const
    {
        return author_;

    }

    /**
   @param  : the author of the Book
   @post   : sets the Book's author to the value of the parameter
    */
    void Book::setAuthor(const std::string& author)
    {
        author_=author;
    }

    /**
        @return : the ISBN value
    */
    long long int Book::getISBN() const
    {
        return ISBN_;

    }

    void Book::setISBN(long long int ISBN)
    {
        ISBN_ = ISBN;
    }


    /**
        @return : the keywords
    */
    const int* Book::getIcon() const
    {
        return icon_;

    }

    void Book::setIcon(int* icon)
    {
    // Create a unique_ptr to hold a copy of the icon data
    std::unique_ptr<int[]> icon_copy(new int[80]);
    std::copy(icon, icon + 80, icon_copy.get());

    icon_ = icon;

    }
    

    
    /**
        @return : the book price
    */
    float Book::getPrice() const
    {
        return price_;
    }

    void Book::setPrice(float price) 
    {
        price_ = price;
    // Set precision to 2 decimal places for output
        std::cout << std::fixed << std::setprecision(2);
    }

    /**
        @return : the keywords
    */
    const std::vector<std::string>& Book::getKeywords() const
    {
        return keywords_;
    }

    void Book::setKeywords(const std::vector<std::string>& keywords)
    {
        this->keywords_ = keywords;
    }

    /**
        @return : the blurb
    */
    const std::string& Book::getBlurb() const
    {
        return blurb_;
    }

    void Book::setBlurb(const std::string& blurb)
    {
        blurb_=blurb;
    }

    void Book::print() const

    {
        std::cout << "Title: " << title_ << "\n";
        std::cout << "Author: " << author_ << "\n";
        std::cout << "ISBN: " << ISBN_ << "\n"; 


        std::cout << "Icon: ";// use for loop to print

        for (int i=0; i<80; i++)
        {
            std::cout<< "\n";
        }
        
        std::cout << "Price: $" << this->getPrice() << std::endl;

        std::string keywords;      
        for (auto kw = this-> getKeywords().begin(); kw != this->getKeywords().end(); kw++)
        {
            keywords += (*kw + ", ");
        }
        keywords = keywords.substr(0, keywords.size() - 2);
        std::cout << "Keywords: "<< keywords << "\n";
        std::cout << "Blurb: " << blurb_ << std::endl;

    }