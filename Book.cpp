#include "Book.hpp"

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
        // clears keyword

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
    
    /**
   @param  : the ISBN of the Book
   @post   : sets the ISBN to the value of the parameter
    */
    void Book::setISBN(long long int ISBN)
    {
        ISBN_ = ISBN;
    }

    /**
        @return : the icons
    */
    const int* Book::getIcon() const
    {
        return icon_;

    }
    
    /**
   @param  : the icon of the Book
   @post   : sets the icon to the value of the parameter
    */
    void Book::setIcon(int* icon)
    {
        if (!icon) {
            throw std::invalid_argument("Invalid icon: pointer cannot be null.");
        }

        if (*icon != 80) {
            throw std::invalid_argument("Invalid icon: expected 80 integers.");
        }

        for (int i = 0; i < 80; ++i) 
        {
            if (icon[i] < 0 || icon[i] > 255) 
            {
                throw std::invalid_argument("Invalid icon value: must be between 0 and 255.");
            }
        }

        // Copy the icon data (assumes caller takes responsibility for managing memory)
        icon_ = new int[80];
        std::copy(icon, icon + 80, icon_);
    }
    
    /**
        @return : the book price
    */
    float Book::getPrice() const
    {
        return price_;
    }

    /**
   @param  : the price of the Book
   @post   : sets the price to the value of the parameter
    */
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

    /**
   @param  : the keywords of the Book
   @post   : sets the keywords to the value of the parameter
    */
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

    /**
   @param  : the blurb of the Book
   @post   : sets the blurb to the value of the parameter
    */
    void Book::setBlurb(const std::string& blurb)
    {
        blurb_=blurb;
    }

    /* print function in the format of text file*/
    void Book::print() const

    {
        std::cout << "Title: " << title_ << "\n";
        std::cout << "Author: " << author_ << "\n";
        std::cout << "ISBN: " << ISBN_ << "\n"; 
        std::string icon;
        int *iconptr = icon_;
        //Creates a pointer named iconptr that points to the first element of the integer array managed by icon_.
        for (int i=0; i<80; i++)
        {
            //Dereferences iconptr to access the current integer value
            icon+= std::to_string(*iconptr) + " ";
            iconptr++;
        }
        // Extracts a substring from icon, starting from index 0 (the beginning) and ending at the second-to-last character
        icon= icon.substr(0, icon.size()-1);
        std::cout << "Icon: "<< icon << std::endl;
        std::cout << "Price: $" << this->getPrice() << std::endl;
        //Declares an empty string variable named keywords to store the concatenated keyword string.
        std::string keywords;      
        //points to the beginning of the keywords container 
        for (auto kw = this-> getKeywords().begin(); kw != this->getKeywords().end(); kw++)
        {
            //Dereferences kw to access the current keyword and increments kw 
            keywords += (*kw + ", ");
        }
        keywords = keywords.substr(0, keywords.size() - 2);
        std::cout << "Keywords: "<< keywords << "\n";
        std::cout << "Blurb: " << blurb_ << std::endl;
    }