#include "magazine.h"
#include <iostream>

Magazine::Magazine() : Publication(), issueNumber(1), publicationMonth("") {}

Magazine::Magazine(const std::string& id, const std::string& title,
                   const std::string& author, const std::string& genre,
                   int pageCount, bool isAvailable,
                   int issueNumber, const std::string& publicationMonth)
    : Publication(id, title, author, genre, pageCount, isAvailable),
      issueNumber(issueNumber), publicationMonth(publicationMonth) {}

int Magazine::getIssueNumber() const { return issueNumber; }
std::string Magazine::getPublicationMonth() const { return publicationMonth; }

void Magazine::setIssueNumber(int issue) { issueNumber = issue; }
void Magazine::setPublicationMonth(const std::string& month) { publicationMonth = month; }

void Magazine::display() const {
    std::cout << "=== Magazine Information ===\n";
    Publication::display();
    std::cout << "Issue Number: " << issueNumber << "\n";
    std::cout << "Publication Month: " << publicationMonth << "\n";
    std::cout << "============================\n";
}

std::string Magazine::getType() const {
    return "Magazine";
}

std::string Magazine::toFileString() const {
    std::string base = Publication::toFileString();
    return base + " " + std::to_string(issueNumber) + " \"" + publicationMonth + "\"";
}