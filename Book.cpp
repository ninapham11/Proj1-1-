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
        std::vector<int> isbn_;
    // Validate ISBN length (should be 10 digits)
        if (std::to_string(ISBN).length() != 10) 
        {
            throw std::invalid_argument("Invalid ISBN format (must be 10 digits)");
        }

        // Extract the last 80 digits of the ISBN as a string
        std::string icon_digits = std::to_string(ISBN).substr(5); // Assuming 10-digit ISBN with first 5 digits for other info

        // Validate each digit and store the valid ones in a vector
        std::vector<int> valid_digits;
        for (char digit_char : icon_digits) 
        {
            int digit = digit_char - '0'; // Convert character to integer
            if (digit >= 0 && digit <= 255) 
            {
            valid_digits.push_back(digit);
            } else 
            {
            throw std::invalid_argument("Invalid icon bitmap digit: " + std::to_string(digit));
            }
        }  

        if (valid_digits.size() != 80) 
        {
            throw std::invalid_argument("Not enough valid icon bitmap digits");
        }
    // Assign the valid digits to the isbn_ member variable (assuming it's a vector<int>)
        isbn_ = valid_digits;

    // Store the ISBN
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
        // Move the ownership of the provided icon data to the member variable
        icon_ = std::move(icon);

        // If the icon is null, set the icon pointer to null to avoid dangling pointer issues
        if (icon_ == nullptr) 
        {
            icon_ = nullptr;
        }
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
        keywords_=keywords;
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
        std::string icon;
        int *icon_ptr = icon_;
        for(int i =0; i<80; i++)
        {
            icon += std::to_string(*icon_ptr) + " ";
            icon_ptr++;
        }

        icon= icon.substr(0, icon.size() - 1);
        std::cout << "Icon: " << icon << std::endl;
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