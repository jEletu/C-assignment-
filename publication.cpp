#include "publication.h"

Publication::Publication() : id(""), title(""), author(""), genre(""), 
                           pageCount(0), isAvailable(true) {}

Publication::Publication(const std::string& id, const std::string& title,
                       const std::string& author, const std::string& genre,
                       int pageCount, bool isAvailable)
    : id(id), title(title), author(author), genre(genre), 
      pageCount(pageCount), isAvailable(isAvailable) {}

// Getters implementation
std::string Publication::getId() const { return id; }
std::string Publication::getTitle() const { return title; }
std::string Publication::getAuthor() const { return author; }
std::string Publication::getGenre() const { return genre; }
bool Publication::getAvailability() const { return isAvailable; }
int Publication::getPageCount() const { return pageCount; }

// Setters implementation
void Publication::setId(const std::string& id) { this->id = id; }
void Publication::setTitle(const std::string& title) { this->title = title; }
void Publication::setAuthor(const std::string& author) { this->author = author; }
void Publication::setGenre(const std::string& genre) { this->genre = genre; }
void Publication::setAvailability(bool available) { isAvailable = available; }
void Publication::setPageCount(int count) { pageCount = count; }

void Publication::display() const {
    std::cout << "ID: " << id << "\n";
    std::cout << "Title: " << title << "\n";
    std::cout << "Author: " << author << "\n";
    std::cout << "Genre: " << genre << "\n";
    std::cout << "Pages: " << pageCount << "\n";
    std::cout << "Available: " << (isAvailable ? "Yes" : "No") << "\n";
}

std::string Publication::getType() const {
    return "Publication";
}

std::string Publication::toFileString() const {
    return id + " \"" + title + "\" \"" + author + "\" \"" + genre + "\" " +
           std::to_string(pageCount) + " " + (isAvailable ? "1" : "0");
}
