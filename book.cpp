#include "book.h"
#include <iostream>

Book::Book() : Publication(), isbn(""), edition(1) {}

Book::Book(const std::string& id, const std::string& title,
           const std::string& author, const std::string& genre,
           int pageCount, bool isAvailable,
           const std::string& isbn, int edition)
    : Publication(id, title, author, genre, pageCount, isAvailable),
      isbn(isbn), edition(edition) {}

std::string Book::getIsbn() const { return isbn; }
int Book::getEdition() const { return edition; }

void Book::setIsbn(const std::string& isbn) { this->isbn = isbn; }
void Book::setEdition(int edition) { this->edition = edition; }

void Book::display() const {
    std::cout << "=== Book Information ===\n";
    Publication::display();
    std::cout << "ISBN: " << (isbn.empty() ? "N/A" : isbn) << "\n";
    std::cout << "Edition: " << edition << "\n";
    std::cout << "========================\n";
}

std::string Book::getType() const {
    return "Book";
}

std::string Book::toFileString() const {
    std::string base = Publication::toFileString();
    return base + " \"" + isbn + "\" " + std::to_string(edition);
}

