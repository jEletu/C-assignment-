#ifndef BOOK_H
#define BOOK_H

#include "publication.h"
#include <string>

class Book : public Publication {
private:
    std::string isbn;
    int edition;

public:
    Book();
    Book(const std::string& id, const std::string& title, 
         const std::string& author, const std::string& genre,
         int pageCount, bool isAvailable = true,
         const std::string& isbn = "", int edition = 1);
    
    // Getters
    std::string getIsbn() const;
    int getEdition() const;
    
    // Setters
    void setIsbn(const std::string& isbn);
    void setEdition(int edition);
    
    // Override virtual methods
    void display() const override;
    std::string getType() const override;
    std::string toFileString() const override;
};

#endif
