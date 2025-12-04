#include "journal.h"
#include <iostream>
#include <sstream>

// Default constructor
Journal::Journal() 
    : Publication(), volume(1), issueNumber(1), publisher(""), issn("") {}

// Parameterized constructor
Journal::Journal(const std::string& id, const std::string& title,
                 const std::string& author, const std::string& genre,
                 int pageCount, bool isAvailable,
                 int volume, int issueNumber,
                 const std::string& publisher, const std::string& issn)
    : Publication(id, title, author, genre, pageCount, isAvailable),
      volume(volume), issueNumber(issueNumber), 
      publisher(publisher), issn(issn) {}

// Getters
int Journal::getVolume() const { return volume; }
int Journal::getIssueNumber() const { return issueNumber; }
std::string Journal::getPublisher() const { return publisher; }
std::string Journal::getIssn() const { return issn; }

// Setters
void Journal::setVolume(int volume) { this->volume = volume; }
void Journal::setIssueNumber(int issueNumber) { this->issueNumber = issueNumber; }
void Journal::setPublisher(const std::string& publisher) { this->publisher = publisher; }
void Journal::setIssn(const std::string& issn) { this->issn = issn; }

// Override display method
void Journal::display() const {
    std::cout << "=== Journal Information ===\n";
    Publication::display();
    std::cout << "Volume: " << volume << "\n";
    std::cout << "Issue: " << issueNumber << "\n";
    std::cout << "Publisher: " << (publisher.empty() ? "N/A" : publisher) << "\n";
    std::cout << "ISSN: " << (issn.empty() ? "N/A" : issn) << "\n";
    std::cout << "===========================\n";
}

// Override getType method
std::string Journal::getType() const {
    return "Journal";
}

// Override toFileString method for saving to file
std::string Journal::toFileString() const {
    std::string base = Publication::toFileString();
    return base + " " + std::to_string(volume) + " " + 
           std::to_string(issueNumber) + " \"" + publisher + "\" \"" + issn + "\"";
}

// Journal-specific method for academic citation
std::string Journal::getFullCitation() const {
    std::ostringstream oss;
    oss << author << ". \"" << title << ".\" ";
    if (!publisher.empty()) {
        oss << publisher << ", ";
    }
    oss << "vol. " << volume << ", no. " << issueNumber << ", ";
    oss << "pp. " << pageCount << " pages.";
    return oss.str();
}